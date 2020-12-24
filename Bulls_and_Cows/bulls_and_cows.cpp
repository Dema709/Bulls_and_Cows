#include "bulls_and_cows.h"
#include "settingswidget.h"

#include <QBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include "../Common/random.hpp"
#include <map>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCompleter>

//#include <QDebug>

Bulls_and_Cows::Bulls_and_Cows(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Быки и коровы");//Название окна

    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonsLayout);
    QPushButton * newGamePushButton = new QPushButton("Новая игра");
    QPushButton * settingsPushButton = new QPushButton("Настройки");
    QPushButton * rulesPushButton = new QPushButton("Правила");
    QPushButton * exitPushButton = new QPushButton("Выход");
    buttonsLayout->addWidget(newGamePushButton);
    buttonsLayout->addWidget(settingsPushButton);
    buttonsLayout->addWidget(rulesPushButton);
    buttonsLayout->addWidget(exitPushButton);

    QHBoxLayout * answerLayout = new QHBoxLayout();
    mainLayout->addLayout(answerLayout);
    QLabel * label = new QLabel("Число:");
    answerLineEdit = new QLineEdit();
    answerPushButton = new QPushButton("ОК");
    answerLayout->addWidget(label);
    answerLayout->addWidget(answerLineEdit);
    answerLayout->addWidget(answerPushButton);

    textTableWidget = new QTextTableWidget();
    textTableWidget->setAlignment(Qt::AlignCenter);//Расположение текста внутри ячейки
    textTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//Ширина столбцов
    mainLayout->addWidget(textTableWidget);

    textTableWidget->setColumnCount(2);
    textTableWidget->setHorizontalHeaderLabels({"Guess", "Result"});

    connect(newGamePushButton, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(settingsPushButton, SIGNAL(clicked()), this, SLOT(showSettings()));
    connect(rulesPushButton, SIGNAL(clicked()), this, SLOT(showRules()));
    connect(exitPushButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(answerPushButton, SIGNAL(clicked()), this, SLOT(answerPushButtonClicked()));

    newGame();
}

Bulls_and_Cows::~Bulls_and_Cows()
{
}

void Bulls_and_Cows::newGame(){
    textTableWidget->clearContents();
    textTableWidget->setRowCount(0);

    secretString.clear();
    if (uniqueSecretNumbers){
        QVector<int> v;
        for (int i=0; i<10; i++)
            v.push_back(i);

        for (int i=0; i<secretStringSize; i++){
            int numToAdd = effolkronium::random_static::get<int>(0, v.size()-1);
            secretString.push_back('0'+v[numToAdd]);
            v.removeAt(numToAdd);
        }
    } else {
        for (int i=0; i<secretStringSize; i++){
            secretString.push_back(effolkronium::random_static::get<char>('0', '9'));
        }
    }

    answerPushButton->setEnabled(true);
    answerLineEdit->setText("");
    answerLineEdit->setMaxLength(secretStringSize);

    QString placeholder;
    for (int i=0; i<secretStringSize; i++) placeholder.push_back("*");
    answerLineEdit->setPlaceholderText(placeholder);
}

void Bulls_and_Cows::showSettings(){
    if (!settingsWidget){
        settingsWidget = std::make_unique<SettingsWidget>(secretStringSize, uniqueSecretNumbers);//c++14
        connect(settingsWidget.get(), SIGNAL(updateSettings(int, bool)), this, SLOT(updateSettings(int, bool)));
        settingsWidget->setWindowModality(Qt::ApplicationModal);//Блокировка основного окна при открытых настройках
    }
    settingsWidget->show();
}

void Bulls_and_Cows::updateSettings(int secretStringSize, bool uniqueSecretNumbers){
    this->secretStringSize = secretStringSize;
    this->uniqueSecretNumbers = uniqueSecretNumbers;
    newGame();
}

void Bulls_and_Cows::showRules(){

    QFile file("bulls_and_cows_rules.txt");
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this, tr("InsertDataWidget"),
                             tr("readEthnicGroups() cannot open file\n"
                                "Aborting..."));
        //abort();
        //Не уверен, что лучше делать: продолжать ограниченную работу (например, вывод данных) или нет
        //Плюс говорят, что в Qt исключениями обычно не пользуются.
    }



    QString rules;
    QTextStream fin(&file);
    fin.setCodec("UTF-8");//Для корректного отображения кириллицы
    bool first_line = true;
    while (!fin.atEnd()){
        if (first_line){
            first_line = false;
        } else {
            rules += '\n';
        }
        rules += fin.readLine();
    }



    QMessageBox::information(this, tr("Правила"), rules);
}

void Bulls_and_Cows::answerPushButtonClicked(){
    if (secretString.size() != answerLineEdit->text().size()) return;

    textTableWidget->setText(textTableWidget->rowCount(),     0, answerLineEdit->text());
    QString hint = getHint(answerLineEdit->text());
    textTableWidget->setText(textTableWidget->rowCount() - 1, 1, hint);

    textTableWidget->scrollToBottom();

    if (std::stoi(hint.toStdString()) == secretString.size()){
        answerPushButton->setDisabled(true);
        QMessageBox::information(this, tr("Победа!"), "Вы выиграли! ;)");
    }

}

QString Bulls_and_Cows::getHint(QString guess){
    QString answer;
    int bulls_count = 0, cows_count = 0;
    std::map<QChar, int> secret_map, guess_map;
    for (int i=0; i<secretString.size(); i++){
        if (secretString[i]==guess[i]){
            bulls_count++;
        } else {
            secret_map[secretString[i]]++;
            guess_map[guess[i]]++;
        }
    }
    for (auto p : guess_map){
        if (secret_map.count(p.first)!=0){
            cows_count += std::min(p.second, secret_map[p.first]);
        }
    }

    //Вывод (формирование ответа):
    QString temp; temp.setNum(bulls_count);
    for (auto c : temp){
        answer.push_back(c);
    }
    answer.push_back('A');
    temp.setNum(cows_count);
    for (auto c : temp){
        answer.push_back(c);
    }
    answer.push_back('B');
    return answer;
}

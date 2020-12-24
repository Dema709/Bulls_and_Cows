#include "settingswidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

//#include <QDebug>

SettingsWidget::SettingsWidget(int secretStringSize, bool uniqueSecretNumbers, QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Настройки");//Название окна
    QGridLayout * mainLayout = new QGridLayout(this);

    QLabel * secretStringSizeLabel = new QLabel("Размер тайного числа");
    secretStringSizeSpinBox = new QSpinBox();
    secretStringSizeSpinBox->setRange(1,10);

    mainLayout->addWidget(secretStringSizeLabel,0,0);
    mainLayout->addWidget(secretStringSizeSpinBox,0,1);

    QLabel * uniqueSecretNumbersLabel = new QLabel("Уникальность символов в числе");
    uniqueSecretNumbersCheckBox = new QCheckBox();

    mainLayout->addWidget(uniqueSecretNumbersLabel,1,0);
    mainLayout->addWidget(uniqueSecretNumbersCheckBox,1,1);

    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonsLayout,2,0,1,2);
    QPushButton * acceptPushButton = new QPushButton("Сохранить");
    QPushButton * cancelPushButton = new QPushButton("Отмена");
    buttonsLayout->addWidget(acceptPushButton);
    buttonsLayout->addWidget(cancelPushButton);

    connect(acceptPushButton, SIGNAL(clicked()), this, SLOT(acceptUpdate()));
    connect(cancelPushButton, SIGNAL(clicked()), this, SLOT(close()));

    this->secretStringSize = secretStringSize;
    this->uniqueSecretNumbers = uniqueSecretNumbers;
    secretStringSizeSpinBox->setValue(secretStringSize);
    uniqueSecretNumbersCheckBox->setChecked(uniqueSecretNumbers);
}

void SettingsWidget::closeEvent(QCloseEvent *event){
    //cancelUpdate();
    //this->hide();
    secretStringSizeSpinBox->setValue(secretStringSize);
    uniqueSecretNumbersCheckBox->setChecked(uniqueSecretNumbers);

}

void SettingsWidget::acceptUpdate(){
    secretStringSize = secretStringSizeSpinBox->value();
    uniqueSecretNumbers = uniqueSecretNumbersCheckBox->isChecked();
    emit updateSettings(secretStringSize, uniqueSecretNumbers);
    this->close();
}

#ifndef BULLS_AND_COWS_H
#define BULLS_AND_COWS_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
//#include <memory>

#include "../Common/QTextTableWidget.h"
class SettingsWidget;

class Bulls_and_Cows : public QWidget
{
    Q_OBJECT

public:
    Bulls_and_Cows(QWidget *parent = nullptr);
    ~Bulls_and_Cows();
private slots:
    void newGame();
    void showSettings();
    void updateSettings(int secretStringSize, bool uniqueSecretNumbers);
    void showRules();
    void answerPushButtonClicked();
private:
    QTextTableWidget * textTableWidget;
    QString secretString;
    int secretStringSize = 4;
    bool uniqueSecretNumbers = false;//!!!!!!!!!!!
    QLineEdit * answerLineEdit;
    QPushButton * answerPushButton;
    std::unique_ptr<SettingsWidget> settingsWidget;

    QString getHint(QString guess);
};
#endif // BULLS_AND_COWS_H

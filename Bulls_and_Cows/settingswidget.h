#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(int secretStringSize, bool uniqueSecretNumbers, QWidget *parent = nullptr);
private:
    QSpinBox * secretStringSizeSpinBox;
    QCheckBox * uniqueSecretNumbersCheckBox;
    int secretStringSize;
    bool uniqueSecretNumbers;

    void closeEvent(QCloseEvent *event);
signals:
    void updateSettings(int secretStringSize, bool uniqueSecretNumbers);
private slots:
    void acceptUpdate();
};

#endif // SETTINGSWIDGET_H

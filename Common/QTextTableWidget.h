#ifndef QTEXTTABLEWIDGET_H
#define QTEXTTABLEWIDGET_H

#include <QTableWidget>

//Виджет для простого вывода текста в виде таблицы

class QTextTableWidget : public QTableWidget
{
public:
    QTextTableWidget(QWidget * parent = nullptr);
    void setText(const int row, const int column, const QString &text);
    void setAlignment(uint16_t alignment);//Для заполняемых ячеек (не для всех)
private:
    uint16_t alignment;
};

#endif // QTEXTTABLEWIDGET_H

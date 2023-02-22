#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <QWidget>
#include <QStack>
#include <QLCDNumber>
#include <QString>
#include <QPushButton>

class Calculator : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber *    p_lcd;
    QStack<QString> calc_stack;
    QString         str_display;
private:
    QPushButton * create_button(const QString & str);
    qreal calculate();
private slots:
    void button_clicked();
public:
    Calculator(QWidget * pwgt = nullptr);
};





#endif

#include <QGridLayout>
#include <QRegExp>

#include "calculator.h"

QPushButton * Calculator::create_button(const QString & str)
{
    QPushButton * p_temp = new QPushButton(str);
    p_temp->setMinimumSize(40, 40);
    /*
     * clicked() is a method of QPushButton,
     * NOT obvious if you are noob!
     */
    this->connect(p_temp, SIGNAL(clicked()), this, SLOT(button_clicked()));
    return p_temp;
}

qreal Calculator::calculate()
{
    qreal operand2 = calc_stack.pop().toDouble();
    QString operation = calc_stack.pop();
    qreal operand1 = calc_stack.pop().toDouble();
    qreal result = 0;

    if (operation == "+") result = operand1 + operand2;
    if (operation == "-") result = operand1 - operand2;
    if (operation == "/") result = operand1 / operand2;
    if (operation == "*") result = operand1 * operand2;

    return result;
}

void Calculator::button_clicked()
{
    QString received_mes =
            (qobject_cast<QPushButton *>(this->sender()))->text();

    if (received_mes == "CE")
    {
        calc_stack.clear();
        str_display = "";
        p_lcd->display("0");
        return;
    }
    if (received_mes.contains(QRegExp("[0-9]")))
    {
        str_display += received_mes;
        p_lcd->display(str_display.toDouble());
    }
    else if (received_mes == ".")
    {
        str_display += received_mes;
        p_lcd->display(str_display);
    }
    else    // "arithmetic operation" pressed
    {
        if (calc_stack.count() >= 2)
        {
            /*
             * a note for noobs:
             *  displayed by class QLCDNumber value is strored
             *  in its private member, so you can access it
             *  via "QLCDNumber.value()" method.
             */
            calc_stack.push(QString().setNum(p_lcd->value()));
            qreal result = calculate();
            p_lcd->display(result);
            calc_stack.clear();
            calc_stack.push(QString().setNum(result));

            /*
             * if we want to do arithmetic operations
             * with already calculated result, then push last operator
             * to stack as well
             */
            if (received_mes != "=")
            {
                calc_stack.push(received_mes);
                str_display = "";
            }
        }
        else // if it is first pressing of digit and ar.operator
        {
            calc_stack.push(QString().setNum(p_lcd->value()));
            calc_stack.push(received_mes);
            str_display = "";
        }
    }

}

Calculator::Calculator(QWidget * pwgt) : QWidget(pwgt)
{
    p_lcd = new QLCDNumber(12);
    p_lcd->setSegmentStyle(QLCDNumber::Flat);
    p_lcd->setMinimumSize(150, 50);

    QChar buttons[4][4] = {
                            {'7', '8', '9', '/'},
                            {'4', '5', '6', '*'},
                            {'1', '2', '3', '-'},
                            {'0', '.', '=', '+'},
                          };

    // layout setup
    QGridLayout * ptop = new QGridLayout;
    ptop->addWidget(p_lcd, 0, 0, 1, 4);
    ptop->addWidget(this->create_button("CE"), 1, 3);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ptop->addWidget(this->create_button(buttons[i][j]), i + 2, j);
        }
    }

    this->setLayout(ptop);
}

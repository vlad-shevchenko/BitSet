#include <QCoreApplication>
#include <QTextStream>
#include <iostream>

#include <expression_evaluator.h>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QTextStream cout(stdout);

    QString expression;
    for (int i = 1; i < argc; ++i) {
        expression += argv[i];
    }

    cout << (new ExpressionEvaluator(expression))->evaluate().toString();

    //return a.exec();
}

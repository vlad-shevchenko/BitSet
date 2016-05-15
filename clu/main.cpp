#include <QCoreApplication>
#include <QTextStream>
#include <iostream>

#include <../BitSet/bitset.cpp>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QTextStream cout(stdout);
    QString in(argv[1]);

    BitSet bs1(in), bs2("1010101");

    cout << (bs1 & bs2).toString();

    //return a.exec();
}

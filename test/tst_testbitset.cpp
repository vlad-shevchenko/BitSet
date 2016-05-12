#include <QString>
#include <QtTest>

#include <../BitSet/bitset.cpp>
#include <iostream>

class TestBitSet : public QObject
{
    Q_OBJECT

public:
    TestBitSet();

private Q_SLOTS:

    void testCreateEmpty()
    {
        BitSet bs;
        QVERIFY(bs.length() == 0);
    }

    void testCreateFromString()
    {
        BitSet bs(QString("10"));

        QVERIFY(bs.length() == 2);
        QVERIFY(bs.get(0) == true);
        QVERIFY(bs.get(1) == false);
    }

    void testCreateFromList()
    {
        QList<bool> list;
        list.push_back(true);
        list.push_back(false);

        BitSet bs(list);

        QVERIFY(bs.length() == 2);
        QVERIFY(bs.get(0) == true);
        QVERIFY(bs.get(1) == false);
    }

    void testCopyBitSet()
    {
        BitSet bs(QString("10"));
        QVERIFY(true);
        BitSet bs2(bs);

        QVERIFY(bs2.length() == 2);
        QVERIFY(bs2.get(0) == true);
        QVERIFY(bs2.get(1) == false);
    }

    void testAdd()
    {
        BitSet bs(QString("10"));
        bs.add(true);

        QVERIFY(bs.length() == 3);
        QVERIFY(bs.get(2) == true);
    }

    void testPut()
    {
        BitSet bs(QString("10"));
        bs.put(true, 1);

        QVERIFY(bs.length() == 2);
        QVERIFY(bs.get(1) == true);
    }

    void testPutInTheEnd()
    {
        BitSet bs(QString("10"));
        bs.put(true, bs.length());

        QVERIFY(bs.length() == 3);
        QVERIFY(bs.get(2) == true);
    }
};

TestBitSet::TestBitSet()
{
}

QTEST_APPLESS_MAIN(TestBitSet)

#include "tst_testbitset.moc"

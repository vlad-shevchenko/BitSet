#include <QString>
#include <QtTest>

#include <../BitSet/bitset.cpp>
#include <iostream>

class TestBitSet : public QObject
{
    Q_OBJECT

private Q_SLOTS:

    void testCreateEmpty()
    {
        BitSet bs;
        QVERIFY(bs.length() == 0);
    }

    void testCreateFromString()
    {
        BitSet bs("10");

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
        BitSet bs("10");
        QVERIFY(true);
        BitSet bs2(bs);

        QVERIFY(bs2.length() == 2);
        QVERIFY(bs2.get(0) == true);
        QVERIFY(bs2.get(1) == false);
    }

    void testAdd()
    {
        BitSet bs("10");
        bs.add(true);

        QVERIFY(bs.length() == 3);
        QVERIFY(bs.get(2) == true);
    }

    void testPut()
    {
        BitSet bs("10");
        bs.put(true, 1);

        QVERIFY(bs.length() == 2);
        QVERIFY(bs.get(1) == true);
    }

    void testPutInTheEnd()
    {
        BitSet bs("10");
        bs.put(true, bs.length());

        QVERIFY(bs.length() == 3);
        QVERIFY(bs.get(2) == true);
    }

    void testPopBit()
    {
        BitSet bs("101");
        bs.pop();

        QVERIFY(bs.length() == 2);
        QVERIFY(bs[0] == true);
        QVERIFY(bs[1] == false);
    }

    void testAddBit()
    {
        BitSet bs("10");
        bs += true;
        QVERIFY(bs.length() == 3);
        QVERIFY(bs.get(2) == true);
    }

    void testAddBitSet()
    {
        BitSet bs1("10"), bs2("01");
        bs1 += bs2;

        QVERIFY(bs1.length() == 4);
        QVERIFY(bs1.get(3) == true);
    }

    void testNegate()
    {
        BitSet bs("10");
        bs = !bs;
        QVERIFY(bs.length() == 2);
        QVERIFY(bs.get(1) == true);
    }

    void testOr()
    {
        BitSet bs1("100"), bs2("101");
        bs1 |= bs2;
        QVERIFY(bs1.length() == 3);
        QVERIFY(bs1.get(0) == true);
        QVERIFY(bs1.get(1) == false);
        QVERIFY(bs1.get(2) == true);
    }

    void testOrOfDifferentLength()
    {
        BitSet bs1("101"), bs2("11");
        bs1 |= bs2;
        QVERIFY(bs1.length() == 3);
        QVERIFY(bs1.get(0) == true);
        QVERIFY(bs1.get(1) == true);
        QVERIFY(bs1.get(2) == true);
    }

    void testAnd()
    {
        BitSet bs1("100"), bs2("101");
        bs1 &= bs2;
        QVERIFY(bs1.length() == 3);
        QVERIFY(bs1.get(0) == true);
        QVERIFY(bs1.get(1) == false);
        QVERIFY(bs1.get(2) == false);
    }

    void testAndOfDifferentLength()
    {
        BitSet bs1("11"), bs2("101");
        bs1 &= bs2;
        QVERIFY(bs1.length() == 3);
        QVERIFY(bs1.get(0) == true);
        QVERIFY(bs1.get(1) == false);
        QVERIFY(bs1.get(2) == false);
    }

    void testXor()
    {
        BitSet bs1("100"), bs2("101");
        bs1 ^= bs2;
        QVERIFY(bs1.length() == 3);
        QVERIFY(bs1.get(0) == false);
        QVERIFY(bs1.get(1) == false);
        QVERIFY(bs1.get(2) == true);
    }

    void testXorOfDifferentLength()
    {
        BitSet bs1("101"), bs2("11");
        bs1 ^= bs2;
        QVERIFY(bs1.length() == 3);
        QVERIFY(bs1.get(0) == false);
        QVERIFY(bs1.get(1) == true);
        QVERIFY(bs1.get(2) == true);
    }

    void testEqual()
    {
        BitSet bs1("100"), bs2("100");
        QVERIFY(bs1 == bs2);
    }

    void testEqualOfDifferentLength()
    {
        BitSet bs1("10"), bs2("101");
        QVERIFY(bs1 != bs2);
    }

    void testNotEqual()
    {
        BitSet bs1("101"), bs2("110");
        QVERIFY(bs1 != bs2);
    }

    void testLeftShift()
    {
        BitSet bs("10");
        bs <<= 2;
        QVERIFY(bs.length() == 4);
        QVERIFY(bs.get(3) == false);
    }

    void testRightShift()
    {
        BitSet bs("1011");
        bs >>= 2;
        QVERIFY(bs.length() == 2);
        QVERIFY(bs.get(0) == true);
        QVERIFY(bs.get(1) == true);
    }

    void testSubscriptOperator()
    {
        BitSet bs("101");
        QVERIFY(bs[2] == true);
    }

    void testPutOutOfRange()
    {
        BitSet bs("10");
        QVERIFY_EXCEPTION_THROWN(bs.put(true, 3), BitSet::OutOfRangeException);
    }

    void testGetOutOfRange()
    {
        BitSet bs("10");
        QVERIFY_EXCEPTION_THROWN(bs.get(3), BitSet::OutOfRangeException);
    }

    void testCreateOfInvalidString()
    {
        QVERIFY_EXCEPTION_THROWN(BitSet("42"), BitSet::InvalidRepresentationException);
    }

};

QTEST_APPLESS_MAIN(TestBitSet)

#include "tst_testbitset.moc"

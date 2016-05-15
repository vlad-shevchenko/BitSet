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

    void testCreateOfTwoBlocks()
    {
        BitSet bs("111111111111111111111111111111111111111111111111"); // 48
        QVERIFY(bs.length() == 48);
    }

    void testAddOverBlockSize()
    {
        BitSet bs("11111111111111111111111111111111"); // 32
        bs += true;
        QVERIFY(bs.length() == 33);
        QVERIFY(bs == BitSet("111111111111111111111111111111111")); // 33
    }

    void testOrOnTwoLongSets()
    {
        BitSet bs1("111111111111111111111111111111111111111111111111"), bs2("00000000000000000000000000000000"); //48 and 32
        BitSet result = bs1 | bs2;
        QVERIFY(result.length() == 48);
        QVERIFY(result == BitSet("111111111111111111111111111111111111111111111111")); //48
    }

    void testLeftShiftOverBlockSize()
    {
        BitSet bs("11111111111111111111111111111111"); // 32
        bs <<= 16;
        QVERIFY(bs.length() == 48);
        QVERIFY(bs == BitSet("000000000000000011111111111111111111111111111111")); // 32 + 16
    }

    void testRightShiftOverBlockSize()
    {
        BitSet bs("111111111111111111111111111111111111111111111111"); // 48
        bs >>= 20;
        QVERIFY(bs.length() == 28);
        QVERIFY(bs == BitSet("1111111111111111111111111111")); // 28
    }

    void testNegateLongSet()
    {
        BitSet bs("111111111111111111111111111111111111111111111111"); // 48
        bs = !bs;
        QVERIFY(bs.length() == 48);
        QVERIFY(bs == BitSet("000000000000000000000000000000000000000000000000")); // 48
    }

    void testXorWithEmptySet()
    {
        BitSet bs1("1010"), bs2("");
        BitSet xored = bs1 ^ bs2;
        QVERIFY(bs1 == xored);
    }

    void testAndWithEmptySet()
    {
        BitSet bs1("1010"), bs2("");
        QVERIFY((bs1 & bs2) == BitSet("0000"));
    }

    void testPopEmpty()
    {
        BitSet bs;
        QVERIFY_EXCEPTION_THROWN(bs.pop(), BitSet::OutOfRangeException);
    }

    void testPopOverBlockSize()
    {
        BitSet bs("11111111111111111111111111111111"); // 32
        bs.pop();
        QVERIFY(bs == BitSet("1111111111111111111111111111111")); // 31
    }

    void testPutOverBlockSize()
    {
        BitSet bs("11111111111111111111111111111111"); // 32
        bs.put(false, 32);
        QVERIFY(bs.length() == 33);
        QVERIFY(bs == BitSet("111111111111111111111111111111110")); // 32 + 1
    }

    void testToString()
    {
        BitSet bs("1010101");
        bs.add(false);
        QVERIFY(bs.toString() == "10101010");
    }

};

QTEST_APPLESS_MAIN(TestBitSet)

#include "tst_testbitset.moc"

#include <QString>
#include <QtTest>

//#include <../BitSet/symbols.h>
//#include <../BitSet/bitset.h>
//#include <../BitSet/lexer.h>
//#include <../BitSet/parser.h>
#include <bitset.h>
#include <lexer.h>
#include <parser.h>
#include <symbols.h>

using namespace symbols;

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

    void testCreateFromFile()
    {
        QTemporaryFile file;
        file.open();
        file.write("1010");
        file.seek(0);

        BitSet bs(file);

        QVERIFY(bs == BitSet("1010"));
    }

    void testEmptyExpressionContainsNoTokens()
    {
        Lexer lexer("");
        QVERIFY(lexer.tokenize().size() == 0);
    }

    void testValueExtraction()
    {
        QVERIFY(Lexer("101").tokenize()[0].value() == "101");
    }

    void testTwoSymbols()
    {
        QVERIFY(Lexer("1+").tokenize().size() == 2);
    }

    void testFilePath()
    {
        QVERIFY(Lexer("file:./abc:").tokenize()[0].value() == "./abc");
    }

    void testFilePathFollowedByBitset()
    {
        QList<symbols::Symbol> tokens = Lexer("file:path:101").tokenize();
        QVERIFY(tokens.size() == 2);
        QVERIFY(tokens[0].value() == "path");
        QVERIFY(tokens[1].value() == "101");
    }

    void testAllSymbols()
    {
        QList<symbols::Symbol> tokens = Lexer("file:path: 101 ! & | ^ + <<1 >>2 ( )").tokenize();
        QVERIFY(tokens.size() == 11);
        QVERIFY(tokens[0].is(FILE_PATH));
        QVERIFY(tokens[1].is(BITSET));
        QVERIFY(tokens[2].is(NEGATE));
        QVERIFY(tokens[3].is(AND));
        QVERIFY(tokens[4].is(OR));
        QVERIFY(tokens[5].is(XOR));
        QVERIFY(tokens[6].is(CONCAT));
        QVERIFY(tokens[7].is(LEFT_SHIFT));
        QVERIFY(tokens[8].is(RIGHT_SHIFT));
        QVERIFY(tokens[9].is(OPEN_PAR));
        QVERIFY(tokens[10].is(CLOSE_PAR));
    }

    void testIgnoreWhitespaces()
    {
        QList<symbols::Symbol> tokens = Lexer("  1 + \t \t 0  ").tokenize();
        QVERIFY(tokens.size() == 3);
        QVERIFY(tokens[0].value() == "1");
        QVERIFY(tokens[1].is(CONCAT));
        QVERIFY(tokens[2].value() == "0");
    }

    void testInvalidExpression()
    {
        QVERIFY_EXCEPTION_THROWN(Lexer("1010999900").tokenize(), symbols::InvalidExpressionException);
    }

    void testEmptyFilePath()
    {
        QVERIFY_EXCEPTION_THROWN(Lexer("file::").tokenize(), symbols::InvalidExpressionException);
    }

    void testBitsetAfterShift()
    {
        QList<Symbol> tokens = Lexer("101 >> 2 101").tokenize();
        QVERIFY(tokens[2].value() == "101");
    }

    void testTwoBitsetConcat()
    {
        QList<Symbol> tokens = Lexer("10 + 01").tokenize();
        QVERIFY((new Parser(tokens))->parse() == BitSet("1001"));
    }

    void testTwoOperationsWithDifferentPriorities()
    {
        QList<Symbol> tokens = Lexer("10 + 01 ^ 11").tokenize();
        QVERIFY((new Parser(tokens))->parse() == BitSet("1010"));
    }

    void testParentheses()
    {
        QList<Symbol> tokens = Lexer("(10 + 01) ^ 11").tokenize();
        QVERIFY((new Parser(tokens))->parse() == BitSet("0101"));
    }

    void testParseLeftShift()
    {
        QList<Symbol> tokens = Lexer("101 << 2").tokenize();
        QVERIFY((new Parser(tokens))->parse() == BitSet("00101"));
    }

    void testParseRightShift()
    {
        QList<Symbol> tokens = Lexer("101 >> 2").tokenize();
        QVERIFY((new Parser(tokens))->parse() == BitSet("1"));
    }

    void testEndOfExpression()
    {
        QList<Symbol> tokens = Lexer("101 >> 2 101").tokenize();
        QVERIFY_EXCEPTION_THROWN((new Parser(tokens))->parse(), InvalidExpressionException);
    }

};

QTEST_APPLESS_MAIN(TestBitSet)
#include "tst_bitset.moc"

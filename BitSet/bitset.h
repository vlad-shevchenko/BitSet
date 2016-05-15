#ifndef BITSET_H
#define BITSET_H

#include "bitset_global.h"

#include <exception>

#include <QList>
#include <QFile>
#include <QString>

class BitSet
{
    QList<quint32> set;
    int bitLength;

    void createOfList(QList<bool>& set);

public:

    static const int BLOCK_SIZE = 32;

    /**
     * @brief BitSet Creates an empty bitset.
     */
    BitSet();

    /**
     * @brief BitSet Parses string representation of bitset and creates a bitset of it. Representation must start from least significant bits
     * @param representation string containing nothing except sequence of '0' and '1'
     */
    BitSet(QString representation);

    /**
     * @brief BitSet Creates a bitset from a list of boolean.
     * @param set
     */
    BitSet(QList<bool>& set);

    /**
     * @brief BitSet reads a string representation of a bitset from a file and uses it
     * to create a bitset. Keeps reading until find any character except '0' and '1'.
     * @param file
     */
    BitSet(QFile& file);

    BitSet(BitSet& that);

    /**
     * @brief add Appends a bit to the end of a bitset
     * @param bit
     */
    void add(const bool bit);

    // TODO vlad: check out Qt errors and find an appropriate one
    /**
     * @brief put Puts a bit into a specified position. Throws an error (?) if index is out of bound.
     * Does not throws any error if index is equal to length, so it can be used instead of
     * BitSet::add(bool) method.
     * @param bit
     * @param index
     */
    void put(bool bit, int index);

    const bool get(int index) const;

    bool pop();

    BitSet operator+(const BitSet& that);
    BitSet operator+(const bool bit);
    BitSet& operator+=(const BitSet& that);
    BitSet& operator+=(const bool bit);

    BitSet operator!();

    /**
     * @brief operator |= Performs operation bit-by-bit from the beggining. If lengths of BitSets are different, all unsufficient bits considered false
     * @param that
     * @return new BitSet
     */
    BitSet operator|(const BitSet& that);
    /**
     * @brief operator |= Performs operation bit-by-bit from the beggining. If lengths of BitSets are different, all unsufficient bits considered false
     * @param that
     * @return modified BitSet
     */
    BitSet& operator|=(const BitSet& that);

    /**
     * @brief operator &= Performs operation bit-by-bit from the beggining. If lengths of BitSets are different, all unsufficient bits considered false
     * @param that
     * @return new BitSet
     */
    BitSet operator&(const BitSet& that);
    /**
     * @brief operator &= Performs operation bit-by-bit from the beggining. If lengths of BitSets are different, all unsufficient bits considered false
     * @param that
     * @return modified BitSet
     */
    BitSet& operator&=(const BitSet& that);

    /**
     * @brief operator ^= Performs operation bit-by-bit from the beggining. If lengths of BitSets are different, all unsufficient bits considered false
     * @param that
     * @return new BitSet
     */
    BitSet operator^(const BitSet& that);
    /**
     * @brief operator ^= Performs operation bit-by-bit from the beggining. If lengths of BitSets are different, all unsufficient bits considered false
     * @param that
     * @return modified BitSet
     */
    BitSet& operator^=(const BitSet& that);

    BitSet operator<<(const int shift);
    BitSet& operator<<=(const int shift);

    BitSet operator>>(const int shift);
    BitSet& operator>>=(const int shift);

    bool operator==(const BitSet& that);
    bool operator!=(const BitSet& that);

    BitSet& operator=(BitSet that);

    const bool operator[](int i) const;

    int length() const;

    /**
     * @brief toString Serializes a bitset to a string. The string contains nothing except
     * a sequence of '0' and '1', so it can be than used as an input for BitSet::BitSet(QString) constructor.
     * @return string representation of a bitset
     */
    QString toString();

    /**
     * @brief writeToFile Writes result of BitSet::toString() method to the specified file.
     * @param file
     */
    void writeToFile(QFile file);

    class OutOfRangeException : public std::exception {
        const char * what () const throw ()
        {
          return "Index is out of range";
        }
    };
    class InvalidRepresentationException : public std::exception {
        const char * what () const throw ()
        {
          return "String representation of bitset is incorrect";
        }
     };

};

#endif // BITSET_H

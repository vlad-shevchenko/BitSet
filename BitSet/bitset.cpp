#include "bitset.h"

#include <iostream>

void BitSet::createOfList(QList<bool>& set)
{
    quint32 block = 0;
    int blockLength = 0;
    int bitLength = 0;
    QList<quint32> intSet = QList<quint32>();
    foreach (bool b, set) {
        if (b)
            block |= 1 << blockLength;
        ++blockLength;
        if (blockLength == 32) {
            bitLength += blockLength;
            intSet += block;
            blockLength = 0;
            block = 0;
        }
    }
    if (blockLength != 0) {
        bitLength += blockLength;
        intSet += block;
    }

    this->set = intSet;
    this->bitLength = bitLength;
}

BitSet::BitSet()
{
    this->set = QList<quint32>();
    this->bitLength = 0;
}

BitSet::BitSet(QList<bool>& set)
{
    this->createOfList(set);
}

BitSet::BitSet(BitSet &that)
{
    this->set = QList<quint32>(that.set);
    this->bitLength = that.bitLength;
}

BitSet::BitSet(QString& representation)
{
    QList<bool>* set = new QList<bool>();
    for (int i = 0; i < representation.length(); ++i) {
        QChar ch = representation[i];
        if (ch == '1') {
            set->push_back(true);
        } else if (ch == '0') {
            set->push_back(false);
        } else {
            // TODO vlad:: consider throwing an error
            break;
        }
    }

    createOfList(*set);
}

int BitSet::length()
{
    return this->bitLength;
}

void BitSet::add(bool bit)
{
    quint32 block;
    int blockLength = this->bitLength % 32;
    if (blockLength == 0) {
        block = 0;
        this->set.push_back(block);
    } else {
        block = this->set[this->set.length() - 1];
    }
    std::cout << "before: " << this->set[0];

    if (bit) {
        block |= 1 << blockLength;
        this->set[this->set.size() - 1] = block;
    }
    std::cout << "after: " << this->set[0];
    ++this->bitLength;
}

void BitSet::put(bool bit, int index)
{
    if (index == this->bitLength) {
        this->add(bit);
        return;
    }
    if (index > this->bitLength) {
        // TODO vlad: throw an error
        return;
    }

    int blockIndex = index / 32;
    int bitIndex = index % 32;

    quint32 block = this->set[blockIndex];
    if (bit)
        block |=  (1 << bitIndex);
    else {
        block &= ~(1 << bitIndex);
    }
    this->set[blockIndex] = block;
}

bool BitSet::get(int index)
{
    if (index < 0 || index >= this->bitLength) {
        std::cout << "Error: out of bound" << std::endl;
        // TODO vlad: throw an error
        return false;
    }

    int blockIndex = index / 32;
    int bitIndex = index % 32;
    quint32 block = this->set[blockIndex];
    return !!(block & (1 << bitIndex));
}

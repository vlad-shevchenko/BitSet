#include "bitset.h"

#include <iostream>
#include <algorithm>

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

BitSet::BitSet(QString representation)
{
    QList<bool>* set = new QList<bool>();
    for (int i = 0; i < representation.length(); ++i) {
        QChar ch = representation[i];
        if (ch == '1') {
            set->push_back(true);
        } else if (ch == '0') {
            set->push_back(false);
        } else {
            throw BitSet::InvalidRepresentationException();
        }
    }

    createOfList(*set);
}

int BitSet::length() const
{
    return this->bitLength;
}

void BitSet::add(const bool bit)
{
    quint32 block;
    int blockLength = this->bitLength % 32;
    if (blockLength == 0) {
        block = 0;
        this->set.push_back(block);
    } else {
        block = this->set[this->set.length() - 1];
    }

    if (bit) {
        block |= 1 << blockLength;
        this->set[this->set.size() - 1] = block;
    }
    ++this->bitLength;
}

void BitSet::put(bool bit, int index)
{
    if (index == this->bitLength) {
        this->add(bit);
        return;
    }
    if (index < 0 || index >= this->bitLength) {
        throw BitSet::OutOfRangeException();
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

const bool BitSet::get(int index) const
{
    if (index < 0 || index >= this->bitLength) {
        throw BitSet::OutOfRangeException();
    }

    int blockIndex = index / 32;
    int bitIndex = index % 32;
    quint32 block = this->set[blockIndex];
    return !!(block & (1 << bitIndex));
}

bool BitSet::pop()
{
    if (this->bitLength == 0) {
        throw BitSet::OutOfRangeException();
    }

    int lastBlockIndex;
    int lastBlockLength = this->bitLength % 32;
    if (lastBlockLength == 0) {
        lastBlockIndex = this->bitLength / 32 - 1;
    } else {
        lastBlockIndex = this->bitLength / 32;
    }

    quint32 block = this->set[lastBlockIndex];
    bool lastBit = !!(block & ((1 << lastBlockLength) - 1));

    if (lastBlockLength == 1) {
        this->set.pop_back();
    } else {
        block &= ~(1 << (lastBlockLength - 1));
        this->set[lastBlockIndex] = block;
    }

    --this->bitLength;

    return lastBit;
}

BitSet BitSet::operator+(const BitSet& that)
{
    BitSet result(*this);
    for (int i = 0; i < that.length(); ++i) {
        result.add(that.get(i));
    }
    return result;
}

BitSet BitSet::operator+(const bool bit)
{
    BitSet result(*this);
    result.add(bit);
    return result;
}

BitSet& BitSet::operator+=(const BitSet& that)
{
    for (int i = 0; i < that.length(); ++i) {
        this->add(that[i]);
    }
    return *this;
}

BitSet& BitSet::operator+=(const bool bit)
{
    this->add(bit);
    return *this;
}


BitSet BitSet::operator!()
{
    BitSet bs;
    for (int i = 0; i < this->bitLength; ++i) {
        bool bit = (*this)[i];
        bs.add(!bit);
    }
    return bs;
}

BitSet BitSet::operator|(const BitSet& that)
{
    BitSet bs;
    int maxLength = std::max(this->length(), that.length());
    for (int i = 0; i < maxLength; ++i) {
        if (i < this->length() && i >= that.length()) {
            bs.add((*this)[i]);
        } else if (i >= this->length() && i < that.length()) {
            bs.add(that[i]);
        } else {
            bs.add((*this)[i] || that[i]);
        }
    }
    return bs;
}

BitSet& BitSet::operator|=(const BitSet& that)
{
    int maxLength = std::max(this->length(), that.length());
    for (int i = 0; i < maxLength; ++i) {
        if (i < this->length() && i >= that.length()) {
            this->put((*this)[i], i);
        } else if (i >= this->length() && i < that.length()) {
            this->put(that[i], i);
        } else {
            this->put((*this)[i] || that[i], i);
        }
    }
    return *this;
}

BitSet BitSet::operator&(const BitSet& that)
{
    BitSet bs;
    int maxLength = std::max(this->length(), that.length());
    for (int i = 0; i < maxLength; ++i) {
        if (i >= this->length() || i >= that.length()) {
            bs.add(false);
        } else {
            bs.add((*this)[i] && that[i]);
        }
    }
    return bs;
}

BitSet& BitSet::operator&=(const BitSet& that)
{
    int maxLength = std::max(this->length(), that.length());
    for (int i = 0; i < maxLength; ++i) {
        if (i >= this->length() || i >= that.length()) {
            this->put(false, i);
        } else {
            this->put((*this)[i] && that[i], i);
        }
    }
    return *this;
}

BitSet BitSet::operator^(const BitSet& that)
{
    BitSet bs;
    int maxLength = std::max(this->length(), that.length());
    for (int i = 0; i < maxLength; ++i) {
        if (i < this->length() && i >= that.length()) {
            bs.add((*this)[i]);
        } else if (i >= this->length() && i < that.length()) {
            bs.add(that[i]);
        } else {
            bs.add((*this)[i] ^ that[i]);
        }
    }
    return bs;
}

BitSet& BitSet::operator^=(const BitSet& that)
{
    int maxLength = std::max(this->length(), that.length());
    for (int i = 0; i < maxLength; ++i) {
        if (i < this->length() && i >= that.length()) {
            this->put((*this)[i], i);
        } else if (i >= this->length() && i < that.length()) {
            this->put(that[i], i);
        } else {
            this->put((*this)[i] ^ that[i], i);
        }
    }
    return *this;
}

BitSet BitSet::operator<<(const int shift)
{
    BitSet result;
    for (int i = 0; i < shift; ++i) {
        result.add(false);
    }
    for (int i = 0; i < this->length(); ++i) {
        result.add((*this)[i]);
    }
    return result;
}

BitSet& BitSet::operator<<=(const int shift)
{
    for (int i = 0; i < shift; ++i) {
       this->add(false);
    }
    for (int i = this->length() - shift - 1; i >= shift; --i) {
        this->put((*this)[i - shift], i);
    }
    for (int i = 0; i < shift; ++i) {
        this->put(false, i);
    }
    return *this;
}

BitSet BitSet::operator>>(const int shift)
{
    BitSet result;
    for (int i = shift; i < this->length(); ++i) {
        result.add((*this)[i]);
    }
    return result;
}

BitSet& BitSet::operator>>=(const int shift)
{
    for (int i = shift; i < this->length(); ++i) {
        this->put((*this)[i], i - shift);
    }
    for (int i = 0; i < shift; ++i) {
        this->pop();
    }
    return *this;
}

bool BitSet::operator==(const BitSet& that)
{
    if (this->length() != that.length()) {
        return false;
    }
    for (int i = 0; i < this->length(); ++i) {
        if ((*this)[i] != that[i]) {
            return false;
        }
    }
    return true;
}

bool BitSet::operator!=(const BitSet& that)
{
    return !(this == &that);
}

BitSet& BitSet::operator=(BitSet that)
{
    this->set = that.set;
    this->bitLength = that.bitLength;
    return *this;
}

const bool BitSet::operator[](int i) const
{
    return this->get(i);
}

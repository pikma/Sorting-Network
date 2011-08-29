#include "binary_iterator.h"


BinaryIterator::BinaryIterator(int n) :_n(n)
{
    _permut = new int[n];
    reset();
}

BinaryIterator::BinaryIterator(const BinaryIterator &it) :
    _n(it._n),
    _permut(it._permut),
    _has_element(it._has_element)
{}

BinaryIterator::~BinaryIterator()
{
    delete[] _permut;
}

bool BinaryIterator::has_element() const
{
    return _has_element;
}

BinaryIterator& BinaryIterator::operator++()
{
    int i = _n-1;
    bool keep_incrementing = false;
    do {
        _permut[i] = _permut[i] ^ 1;
        keep_incrementing = (_permut[i] == 0);
        --i;
    } while (i >= 0 && keep_incrementing);

    _has_element = i != -1 || !keep_incrementing;

    return *this;
}

void BinaryIterator::reset()
{
    for (int i = 0; i < _n; i++) {
        _permut[i] = 0;
    }
    _permut[_n-1] = 1; // the permutation with n zeros is not interesting
    _has_element = true;
}

BinaryIterator BinaryIterator::operator++(int) {
    BinaryIterator tmp = *this;
    operator++();
    return tmp;
}

int * BinaryIterator::get() const
{
    return _permut;
}

std::ostream & operator<<(std::ostream & stream, const BinaryIterator & it)
{
    for (int i = 0; i < it._n; ++i) {
        stream << it._permut[i] << " ";
    }
    return stream;
}

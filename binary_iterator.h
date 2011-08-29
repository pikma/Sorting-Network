#include <iostream>

#ifndef BINARY_ITERATOR
#define BINARY_ITERATOR
class BinaryIterator
{
    public:
        BinaryIterator(int n);
        ~BinaryIterator();
        BinaryIterator(const BinaryIterator & it);

        void reset();

        bool has_element() const;
        BinaryIterator& operator++();
        BinaryIterator operator++(int);
        int* get() const;

        friend std::ostream& operator<< (std::ostream& o,
                const BinaryIterator & it);
    private:
        int _n;
        int * _permut;
        bool _has_element;

};
#endif

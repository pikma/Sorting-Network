#include "./swap.h"
#include <iostream>

#ifndef SORT_NETWORK_ITERATOR
#define SORT_NETWORK_ITERATOR
class SortNetworkIterator
{
    public:
        SortNetworkIterator(int n, int l);
        SortNetworkIterator();
        ~SortNetworkIterator();
        SortNetworkIterator(const SortNetworkIterator & it);

        void reset();

        bool has_element();
        SortNetworkIterator& operator++();
        SortNetworkIterator operator++(int);
        Swap** get() const;

        friend std::ostream& operator<< (std::ostream &,
                const SortNetworkIterator &);
        void set(int *);
        void set_at_partition(int i);

    private:
        void populate_sort_network();
        void set_initial_swap_indices();
        inline bool increment_one_swap_no_carry(int i);
        void increment_one_swap_carry(int i);
        void reset_swap_indices_starting_at(int i);

        int _n; // the number of elements to swap
        int _l; // the length of the swap network
        int * _swap_indices; // size 2l
        Swap ** _sort_network; // size l, array of *Swap
        Swap ** _all_swaps; // array of array of *Swap
        bool _has_element;
};

#endif

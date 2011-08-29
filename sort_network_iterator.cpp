#include "./sort_network_iterator.h"
#include "./util.h"


SortNetworkIterator::SortNetworkIterator(int n, int l) :
    _n(n),
    _l(l)
{
    _swap_indices = new int[2*l];
    _sort_network = new Swap*[l];
    _all_swaps = new Swap*[n];
    for (int i = 0; i < n; ++i) {
        _all_swaps[i] = new Swap[n];
        for (int j = 0; j < n; ++j) {
            _all_swaps[i][j] = Swap(i,j);
        }
    }
    reset();
}

SortNetworkIterator::SortNetworkIterator(const SortNetworkIterator &it) :
    _n(it._n),
    _l(it._l),
    _all_swaps(it._all_swaps)
{
    _swap_indices = new int[2*_l];
    for (int i = 0; i < 2*_l; ++i) {
        _swap_indices[i] = it._swap_indices[i];
    }

    _sort_network = new Swap*[_l];
    for (int i = 0; i < _l; i++) {
        _sort_network[i] = it._sort_network[i];
    }
}

SortNetworkIterator::~SortNetworkIterator()
{
    delete[] _swap_indices;
    delete[] _sort_network;
    for (int i = 0; i < _n; ++i) {
        delete[] _all_swaps[i];
    }
    delete[] _all_swaps;
}

bool SortNetworkIterator::has_element()
{
    return _has_element;
}

bool SortNetworkIterator::increment_one_swap_no_carry(int i)
{
    int a = 2*i;
    int b = 2*i + 1;

    _swap_indices[b]++;
    if (_swap_indices[b] == _n) {
        _swap_indices[a]++;
        _swap_indices[b] = _swap_indices[a] + 1;
    }
    // after 1,2 we get 2,3 , which is invalid. In this case we increment
    // the preceding swap
    bool keep_incrementing = _swap_indices[b] == _n;
    if (keep_incrementing) {
        // we restart, and the first swap is 0,1
        _swap_indices[a] = 0;
        _swap_indices[b] = 1;
    }
    return keep_incrementing;
}

void SortNetworkIterator::increment_one_swap_carry(int i)
{
    bool keep_incrementing = false;
    do {
        keep_incrementing = increment_one_swap_no_carry(i);
        i--; // the preceding swap
    } while (i >= 0 && keep_incrementing);

    _has_element &= !keep_incrementing || (i != -1);
    /* We "and" the _has_element member: if the iterator is finished, it can't
     * not be finished later.
     */
}

SortNetworkIterator& SortNetworkIterator::operator++()
{
    int to_increment = _l - 1;
    do {
        increment_one_swap_carry(to_increment);
        reset_swap_indices_starting_at(to_increment+1);

        /* After the standard incrementation, we search for consecutive swaps that
         * are duplicates. Those can be skipped.
         */
        to_increment = -1;
        for (int i = 0; i < _l - 1; ++i) {
            bool is_equal_to_next = _swap_indices[2*i] == _swap_indices[2*i+2]
                    && _swap_indices[2*i+1] == _swap_indices[2*i+3];
            if (is_equal_to_next) {
                to_increment = i+1;
                break;
            }
        }

        /* We found a swap which is equal to its left swap. We have to increment
         * it (with carry), and then set what was right of it to the initial
         * swap sequence. We just stay in the loop.
         */
    } while (to_increment > 0 && _has_element);

    populate_sort_network();
    return *this;
}

void SortNetworkIterator::reset()
{
    reset_swap_indices_starting_at(0);
    _has_element = true;
    populate_sort_network();
}


void SortNetworkIterator::set_at_partition(int partition_ix)
{
    // partition_ix is between 0 and nbSwaps - 1 (included)
    _swap_indices[0] = 0;
    _swap_indices[1] = 1;

    // we set the first swap
    for (int i = 0; i < partition_ix; ++i) {
        increment_one_swap_no_carry(0);
    }

    // now we set the others, and make sure they differ from the previous swap

    _has_element = true;
    populate_sort_network();
}

// safe even if swapIx if out of range
void SortNetworkIterator::reset_swap_indices_starting_at(int swapIx)
{
    int a = 0;
    int b = 1;

    /* Here we make sure that the previous swap is not (0,1). If it is, and if
     * the swap (0,2) exists, we start at (0,2).
     */
    if (swapIx >= 1 && _swap_indices[2*swapIx - 2] == 0 && _swap_indices[2*swapIx - 1] == 1 && _n > 3)
        b = 2;

    for (int i = swapIx; i < _l; ++i) {
        if (b == _n) {
            a++;
            b = a+1;
        }
        if (b >= _n) { // in this case we start over
            a = 0;
            b = 1;
        }
        _swap_indices[2*i] = a;
        _swap_indices[2*i+1] = b;
        b++;
    }


    // for (int i = swapIx; i < _l; ++i) {
        // _swap_indices[2*i] = 0;
        // _swap_indices[2*i+1] = 1;
        // bool equal_to_previous = i > 0 && _swap_indices[2*i] == _swap_indices[2*i-2]
            // && _swap_indices[2*i+1] == _swap_indices[2*i-1];
        // if (equal_to_previous) {
            // /* We don't propagate the carry here. All we want is to have 0,1 -
             // * 0,2 - 0, 1, etc.. Propagating the no carry could lead to some
             // * issues for n = 2, where there is only one possible swap.
             // */
            // increment_one_swap_no_carry(i);
        // }
    // }

}

void SortNetworkIterator::set(int * swap_indices)
{
    Util::copy_array(swap_indices, _swap_indices, 2* _l);
    _has_element = true;
    populate_sort_network();
}

void SortNetworkIterator::populate_sort_network()
{
    for (int i = 0; i < _l; ++i) {
        int k = _swap_indices[2*i];
        int l = _swap_indices[2*i+1];
        _sort_network[i] = &(_all_swaps[k][l]);
        // similar to new Swap(k,l), except that we don't create a new object
    }

}

SortNetworkIterator SortNetworkIterator::operator++(int) {
    SortNetworkIterator tmp = *this;
    operator++();
    return tmp;
}

Swap ** SortNetworkIterator::get() const
{
    return _sort_network;
}

std::ostream & operator<<(std::ostream & stream, const SortNetworkIterator & it) {
    Swap ** sort_network = it.get();
    for (int i = 0; i < it._l; i++) {
        Swap & s = *(sort_network[i]);
        stream << s << " ";
    }
    return stream;
}

#include "./binary_iterator.h"
#include "./sort_network_iterator.h"

#ifndef SORT_NETWORK_FINDER
#define SORT_NETWORK_FINDER

class SortNetworkFinder {
    public:
        SortNetworkFinder(int n, int l, bool stop_at_first_result);
        ~SortNetworkFinder();

        void begin_at(int * swap_indices);

        /* Sets the search to be performed starting at the i-th partition of
         * the set of Sort Networks.
         *
         * There are (n*(n-1))/2  such partitions, and thus i must be between
         * 0 and (n*(n-1))/2 - 1 (inclusive)
         */
        void begin_at(int i);
        void search();
        void operator()();

    private:
        int _n;
        int _l;
        bool _stop_at_first_result;
        int * _tmp_permutation;

        double _total_nb_networks;
        int _nb_valid_networks;
        int _nb_tested_networks_e6;

        SortNetworkIterator _net_it;
        BinaryIterator  _perm_it;

        bool is_network_valid(Swap ** sort_network);
        void apply_sort_network(Swap ** sort_network, int * permutation);
        void print_progress_status(bool erasable = true, bool print_current_network = false);
        void print_end_message();
};

#endif

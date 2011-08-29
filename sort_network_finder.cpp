#include "./sort_network_finder.h"
#include <iostream>
#include <math.h>
#include "./swap.h"
#include "./util.h"

SortNetworkFinder::SortNetworkFinder(int n, int l, bool stop_at_first_result) :
    _n(n),
    _l(l),
    _stop_at_first_result(stop_at_first_result),
    _nb_valid_networks(0),
    _nb_tested_networks_e6(0),
    _net_it(n, l),
    _perm_it(n)
{
    double nbSwaps = (n * (n-1))/ 2;
    _total_nb_networks = (nbSwaps * pow((double)nbSwaps - 1, (double)l-1));
    _tmp_permutation = new int[n]; // the one we perform the swaps on

}

SortNetworkFinder::~SortNetworkFinder()
{
    delete[] _tmp_permutation;

}

void SortNetworkFinder::apply_sort_network(Swap ** sort_network, int * permutation)
{
    for (int i = 0; i < _l; i++) {
        sort_network[i]->apply(permutation);
    }
}

bool SortNetworkFinder::is_network_valid(Swap ** sort_network) {
    bool is_sort_network_valid = true;
    for (_perm_it.reset(); _perm_it.has_element(); ++_perm_it) {
        // cout << "    Testing " << perm_it << "\n";
        int * binary_permutation = _perm_it.get();
        Util::copy_array(binary_permutation, _tmp_permutation, _n);

        apply_sort_network(sort_network, _tmp_permutation);

        if (!Util::is_sorted(_tmp_permutation, _n)) {
            is_sort_network_valid = false;
            break;
        }
    }
    return is_sort_network_valid;
}

void SortNetworkFinder::print_progress_status(bool erasable, bool print_current_network)
{
    using std::cout;
    double percent = _nb_tested_networks_e6 / _total_nb_networks * 1E6 * 100;
    cout << "[?25l[2K" << _nb_tested_networks_e6 << "e+6 network tested ";
    cout <<"(total: " << _total_nb_networks << ", current: " << percent << "%)";
    if (print_current_network) {
        cout << "\n";
        cout << "[2KCurrent network: " << _net_it;
    }
    if (erasable)
    {
        if (print_current_network)
            cout << "[1A"; //up one row

        cout << "[120D"; // left 120 cols
    }
    else {
        cout << std::endl;
    }

}

void SortNetworkFinder::print_end_message()
{
    using std::cout;
    using std::endl;


    if (_stop_at_first_result) {
        cout << "[2KStopped at the first valid network.\n";
        print_progress_status(false, false);
    }
    else {
        cout << "[2KDone: " << _nb_valid_networks << " valid network"
            << (_nb_valid_networks > 1 ? "s" :"") << " found." << endl;
    }
    cout << "[?25h";
}

void SortNetworkFinder::begin_at(int * swap_indices)
{
    _net_it.set(swap_indices);
}

void SortNetworkFinder::begin_at(int i) // FIXME
{
    int nb_swaps = (_n * (_n - 1 )) / 2;
    int * swap_indices = new int[nb_swaps];

    delete[] swap_indices;
}


void SortNetworkFinder::operator()()
{
    search();
}

void SortNetworkFinder::search()
{
    using std::cout;
    using std::endl;


    cout << "Network with " << _n << " inputs, solutions with " << _l << " comparators.\n";

    unsigned long count = 0;
    _nb_tested_networks_e6 = 0;
    for (; _net_it.has_element(); ++_net_it) {
        Swap ** sort_network = _net_it.get();
        bool is_sort_network_valid = is_network_valid(sort_network);

        if (is_sort_network_valid) {
            _nb_valid_networks++;
            cout << _net_it << " is valid!\n";
            if (_stop_at_first_result)
                break;
        }

        count++;
        if (count == 1000000) {
            count=0;
            _nb_tested_networks_e6++;
            print_progress_status(true, true);
        }
    }

    print_end_message();
}

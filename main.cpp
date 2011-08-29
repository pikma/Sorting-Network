#include <stdio.h>
#include <math.h>
#include <string.h>
#include "./util.h"
#include "./sort_network_finder.h"

using namespace std;

int main(int argc, char** argv)
{
    ASSERT(argc > 2, "I need two arguments (n and l), for the size of the permutation");
    int n = atoi(argv[1]);
    int l = atoi(argv[2]);

    bool stop_at_first = (argc > 3 && strcmp(argv[3], "-first") == 0);

    SortNetworkFinder finder(n, l,stop_at_first);
    // int swap_indices[24] = {1, 2, 4, 5, 0, 2, 3, 5, 0, 1, 3, 4, 1, 4, 0, 3, 2, 5, 1, 3, 2, 4, 2, 1};
    // finder.begin_at(swap_indices);
    finder.search();


    // for (SortNetworkIterator it(n,l); it.has_element(); ++it)
    // {
        // cout << it << endl;
    // }
    // cout << "Done";
}


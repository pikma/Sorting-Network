#include "./swap.h"

Swap::Swap(int i, int j):
    _i(i < j ? i : j), // the min
    _j(i < j ? j : i) // the max
{}


std::ostream & operator<<(std::ostream & s, const Swap& swap)
{
    s << "(" << swap._i << ", " << swap._j << ")";
    return s;
}

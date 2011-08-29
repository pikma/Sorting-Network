#include <string>
#include <iostream>

#ifndef __SWAP_H
#define __SWAP_H
class Swap {
    public:
        Swap(int, int);
        Swap(){}
        void apply(int*);
        std::string to_string();

        friend std::ostream& operator<< (std::ostream& o, Swap const& swap);

    private:
        int _i;
        int _j;
};

inline
void Swap::apply(int * array)
{
    // bool i_bigger = array[_i] > array[_j];

    // int min = i_bigger ? array[_j]: array[_i];
    // int max = i_bigger ? array[_i]: array[_j];
    // array[_i] = min;
    // array[_j] = max;

    if (array[_i] > array[_j]) {
        int tmp = array[_i];
        array[_i] = array[_j];
        array[_j] = tmp;
    }
}
#endif

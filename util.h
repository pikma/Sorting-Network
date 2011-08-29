#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition, ...) do {if (!(condition)) { \
    fprintf(stderr, "File %s, line %d:\n", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
    exit(EXIT_FAILURE); \
}}while(0)

class Util
{
    public:
    template <class T>
        static void copy_array(T *from, T *to, int n)
        {
            for (int i = 0; i < n; ++i) {
                to[i] = from[i];
            }

        }

    template <class T>
        static bool is_sorted(T* array, int n)
        {
            for (int i = 1; i < n; ++i) {
                if (array[i-1] > array[i])
                    return false;
            }
            return true;

        }
};

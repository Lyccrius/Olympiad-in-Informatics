#include <iostream>
#include "quantumbreak.h"

typedef double dbl;

const int maxN = 16;

int query_xor(int n, int t) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < (1 << n); i++) {
        dbl t = arbitary_query(i);
        if (t > 0) {
            if (x == 0) {
                x = i;
            } else {
                y = i;
            }
            if (y) break;
        }
    }
    return x ^ y;
}
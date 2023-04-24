#include "quantumbreak.h"
#include <cmath>

typedef double dbl;

const dbl eps = 1e-6;

namespace subtask {
    namespace _1 {
        int solve(int n) {
            int ret = 0;
            for (int i = 0; i < (1 << n); i++) {
                if (arbitary_query(i) > eps) {
                    ret ^= i;
                }
            }
            return ret;
        }
    }

    namespace _2 {
        dbl A[2][2];

        int solve(int n) {
            A[0][0] = 1.0;
            A[1][0] = 1.0;
            int ret = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j) continue;
                    arbitary_manipulate(A, j);
                }
                if (arbitary_query(0) && arbitary_query(1 << i)) {
                    ret ^= (1 << i);
                }
                query();
            }
            return ret;
        }
    }

    namespace _3 {
        dbl A[2][2];

        int solve(int n) {
            A[0][0] = 1;
            int ret = 0;
            for (int i = 0; i < n; i++) {
                int flag = true;
                for (int j = 1; j <= 12; j++) {
                    arbitary_manipulate(A, i);
                    if (query() == 0) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    ret ^= 1 << i;
                }
            }
            return ret;
        }
    }

    namespace _4 {
        dbl A[2][2];

        int solve(int n) {
            A[0][0] = 1.0 / sqrt(2);
            A[0][1] = 1.0 / sqrt(2);
            A[1][0] = 1.0 / sqrt(2);
            A[1][1] = - 1.0 / sqrt(2);
            int ret = 0;
            for (int i = 0; i < n; i++) {
                manipulate(A, i);
            }
            for (int i = 0; i < n; i++) {
                if (fabs(arbitary_query(1 << i)) < eps) {
                    ret ^= (1 << i);
                }
            }
            return ret;
        }  
    }
}

int query_xor(int n, int t) {
    if (t == 1) return subtask::_1::solve(n);
    if (t == 2) return subtask::_2::solve(n);
    if (t == 3) return subtask::_3::solve(n);
    if (t == 4) return subtask::_4::solve(n);
}
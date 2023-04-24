#include "mythological.h"
#include <stack>

typedef std::stack<int> sic;

const int maxN = 1e5;

namespace ns {
    int a[maxN + 10];
}

void init(int n, int m, int a[], int t) {
    for (int i = 1; i <= n; i++) {
        ns::a[i] = a[i];
    }
    return;
}

int query(int l, int r) {
    sic s;
    int ret = 0;
    for (int i = l; i <= r; i++) {
        if (s.size() && s.top() == ns::a[i]) {
            ret += 2;
            s.pop();
        } else {
            s.push(ns::a[i]);
        }
    }
    return ret;
}
#include "kth.h"

int n_a;
int n_b;
int n_c;
int k;

bool check(int x) {
    int res = 0;
    int l, r;
    l = 0;
    r = n_a;
    while (l < r) {
        int mid = (l + r) / 2;
        if (get_a(mid) >= x) r = mid;
        else l = mid + 1;
    }
    res += l;
    l = 0;
    r = n_b;
    while (l < r) {
        int mid = (l + r) / 2;
        if (get_b(mid) >= x) r = mid;
        else l = mid + 1;
    }
    res += l;
    l = 0;
    r = n_c;
    while (l < r) {
        int mid = (l + r) / 2;
        if (get_c(mid) >= x) r = mid;
        else l = mid + 1;
    }
    res += l;
    return res < k;
}

int query_kth(int n_a, int n_b, int n_c, int k) {
    ::n_a = n_a;
    ::n_b = n_b;
    ::n_c = n_c;
    ::k = k;
    int l = 1;
    int r = 1e9;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
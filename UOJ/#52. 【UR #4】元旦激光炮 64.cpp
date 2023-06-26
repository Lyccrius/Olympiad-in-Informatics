#include "kth.h"

int la, ma, ra;
int lb, mb, rb;
int lc, mc, rc;
int k;

bool check(int x) {
    int res = 0;
    int l, r;
    l = la;
    r = ra;
    while (l < r) {
        int mid = (l + r) / 2;
        if (get_a(mid) >= x) r = mid;
        else l = mid + 1;
    }
    ma = l;
    res += l;
    l = lb;
    r = rb;
    while (l < r) {
        int mid = (l + r) / 2;
        if (get_b(mid) >= x) r = mid;
        else l = mid + 1;
    }
    mb = l;
    res += l;
    l = lc;
    r = rc;
    while (l < r) {
        int mid = (l + r) / 2;
        if (get_c(mid) >= x) r = mid;
        else l = mid + 1;
    }
    mc = l;
    res += l;
    return res < k;
}

int query_kth(int n_a, int n_b, int n_c, int k) {
    ::ra = n_a;
    ::rb = n_b;
    ::rc = n_c;
    ::k = k;
    int l = 1;
    int r = 1e9;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid, la = ma, lb = mb, lc = mc;
        else r = mid - 1, ra = ma, rb = mb, rc = mc;
    }
    return l;
}
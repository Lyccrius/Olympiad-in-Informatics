#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 50000;
const int maxM = 50000;
const int sqrN = 227;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int c[maxN + 10];
int l = 1, r, len;
lxl res, tot;
lxl A[maxM + 10];
lxl B[maxM + 10];

struct Query {
    int i;
    int l, r;

    bool operator<(const Query &other) const {
        if (b[l] != b[other.l]) return l < other.l;
        return r < other.r;
    }
} q[maxM + 10];

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void add(int p) {
    tot += len;
    len++;
    res += c[a[p]];
    c[a[p]]++;
    return;
}

void del(int p) {
    len--;
    tot -= len;
    c[a[p]]--;
    res -= c[a[p]];
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrN + 1;
    for (int i = 1; i <= m; i++) std::cin >> q[i].l >> q[i].r;
    for (int i = 1; i <= m; i++) q[i].i = i;
    std::sort(q + 1, q + m + 1);
    for (int i = 1; i <= m; i++) {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        if (l == r) {
            A[q[i].i] = 0;
            B[q[i].i] = 1;
        } else {
            A[q[i].i] = res / gcd(res, tot);
            B[q[i].i] = tot / gcd(res, tot);
        }
    }
    for (int i = 1; i <= m; i++) std::cout << A[i] << '/' << B[i] << '\n';
    return 0;
}
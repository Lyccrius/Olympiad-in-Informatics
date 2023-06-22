#include <iostream>
#include <algorithm>
#include <cstring>

typedef char chr;
typedef unsigned long long ull;

const int maxN = 1e5;
const int base = 131;

int n;
int m;
chr s[2 * maxN + 10];
int sa[2 * maxN + 10];

struct Hash {
    ull base;
    ull h[2 * maxN + 10];
    ull p[2 * maxN + 10];

    void init(ull base) {
        this->base = base;
        p[0] = 1;
        for (int i = 1; i <= 2 * maxN; i++) p[i] = p[i - 1] * base;
        return;
    }

    void calc(chr *s) {
        for (int i = 1; s[i]; i++) h[i] = h[i - 1] * base + s[i];
    }

    ull ask(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }

    int lcp(int i, int j) {
        int l = 0;
        int r = std::min(m - i + 1, m - j + 1);
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (ask(i, i + mid - 1) == ask(j, j + mid - 1)) l = mid;
            else r = mid - 1;
        }
        return l;
    }
} h;

bool cmp(int i, int j) {
    int k = h.lcp(i, j);
    return s[i + k] < s[j + k];
}

int main() {
    std::cin >> (s + 1);
    n = strlen(s + 1);
    m = n * 2;
    for (int i = 1; i <= n; i++) s[i + n] = s[i];
    for (int i = 1; i <= m; i++) sa[i] = i;
    h.init(base);
    h.calc(s);
    std::sort(sa + 1, sa + m + 1, cmp);
    for (int i = 1; i <= m; i++) if (sa[i] <= n) std::cout << s[sa[i] + n - 1];
    return 0;
}
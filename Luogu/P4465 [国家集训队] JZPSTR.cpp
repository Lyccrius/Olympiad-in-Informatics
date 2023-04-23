#include <iostream>
#include <bitset>
#include <cstring>

typedef char chr;

const int maxN = 1e6;

int T;
int p;
int n;
int x, y;
chr z[maxN + 10];
std::bitset<maxN + 10> a[10];
std::bitset<maxN + 10> t;

void ins() {
    std::cin >> x >> z;
    n = strlen(z);
    for (int i = 0; i < 10; i++) {
        t = (a[i] >> x) << x;
        a[i] ^= t ^ (t << n);
    }
    for (int i = 0; i < n; i++) {
        a[z[i] - '0'][x + i] = true;
    }
    return;
}

void del() {
    std::cin >> x >> y;
    for (int i = 0; i < 10; i++) {
        t = (a[i] >> y) << y;
        a[i] ^= ((a[i] >> x) << x) ^ (t >> (y - x));
    }
    return;
}

void qry() {
    std::cin >> x >> y >> z;
    n = strlen(z);
    t.reset();
    t = ((~t) << x) ^ ((~t) << (y - n + 1));
    for (int i = 0; i < n; i++) {
        if (i) t = t << 1;
        t = t & a[z[i] - '0'];
    }
    std::cout << t.count() << '\n';
    return;
}

void mian() {
    std::cin >> p;
    if (p == 0) ins();
    else if (p == 1) del();
    else if (p == 2) qry();
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}
#include <iostream>
#include <set>

typedef char chr;
typedef unsigned long long ull;
typedef std::set<ull> sut;

const int maxN = 1000;
const int maxM = 1500;
const ull base = 131;

int n;
chr s[maxM + 10];
sut p;

ull hash(chr *str) {
    ull ret = 0;
    for (int i = 1; str[i]; i++) {
        ret = ret * base;
        ret = ret + str[i];
    }
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> (s + 1);
        p.insert(hash(s));
    }
    std::cout << p.size() << '\n';
    return 0;
}
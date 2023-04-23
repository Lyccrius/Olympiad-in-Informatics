#include <iostream>
#include <bitset>

const int maxN = 2e4;

int k;
int n[10];
int s;
int m;
std::bitset<6 * maxN + 10> f;

void mian() {
    s = 0;
    m = 0;
    f.reset();
    f.set(0);
    for (int i = 1; i <= 6; i++) s += i * n[i];
    if (s & 1) {
        std::cout << "Can't be divided." << '\n';
        return;
    }
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= n[i]; j++) {
            f |= (f << i);
        }
    }
    if (f.test(s >> 1)) {
        std::cout << "Can be divided." << '\n';
    } else {
        std::cout << "Can't be divided." << '\n';
    }
    return;
}

int main() {
    while (true) {
        for (int i = 1; i <= 6; i++) std::cin >> n[i];
        if ((n[1] | n[2] | n[3] | n[4] | n[5] | n[6]) == 0) break;
        std::cout << "Collection #" << ++k << ":" << '\n';
        mian();
        std::cout << '\n';
    }
    return 0;
}
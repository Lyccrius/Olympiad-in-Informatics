#include <iostream>

const int maxN = 3000;

int kase;
int l = maxN / 2, r = maxN / 2;
int a[maxN + 10];

bool Build(int p) {
    int x; std::cin >> x;
    if (x == -1) return false; else a[p] += x;
    l = std::min(l, p);
    r = std::max(r, p);
    Build(p - 1);
    Build(p + 1);
    return true;
}

int main() {
    while (Build(maxN / 2)) {
        std::cout << "Case " << ++kase << ":\n";
        for (int i = l; i < r; i++) std::cout << a[i] << ' ', a[i] = 0;
        std::cout << a[r] << '\n' << '\n', a[r] = 0;
        l = maxN / 2;
        r = maxN / 2;
    }
    return 0;
}
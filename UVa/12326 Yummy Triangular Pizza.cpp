#include <iostream>

const int maxN = 16;

int t;
int n;
int a[maxN + 10] = {0, 1, 1, 1, 4, 6, 19, 43, 120, 307, 866, 2336, 6588, 18373, 52119, 147700, 422016};

void mian() {
    std::cin >> n;
    std::cout << a[n] << '\n';
    return;
}

int main() {
    std::cin >> t;
    for (int i = 1; i <= t; i++) {
        std::cout << "Case #" << i << ": ";
        mian();
    }
    return 0;
}
#include <iostream>
#include <algorithm>

const int maxN = 10000;

int N;
int L[maxN + 10];
int ans;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N * 2; i++) std::cin >> L[i];
    std::sort(L + 1, L + N * 2 + 1);
    for (int i = 1; i <= N * 2; i += 2) ans += L[i];
    std::cout << ans;
    return 0;
}
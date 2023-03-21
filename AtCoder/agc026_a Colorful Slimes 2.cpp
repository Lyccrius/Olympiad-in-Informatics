#include <iostream>

const int maxN = 100;

int N;
int a[maxN + 10];

int main() {
    int ans = 0;
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 2; i <= N; i++) if (a[i] == a[i - 1]) ans++, a[i] = 0;
    std::cout << ans << '\n';
    return 0;
}
#include <iostream>
#include <algorithm>

const int maxN = 100;

int N, x;
int a[maxN + 10];
int ans;

int main() {
    std::cin >> N >> x;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    std::sort(a + 1, a + N + 1);
    for (int i = 1; i < N; i++) {
        if (x >= a[i]) {
            x -= a[i];
            ans++;
        } else break;
    }
    if (x == a[N]) ans++;
    std::cout << ans;
    return 0;
}
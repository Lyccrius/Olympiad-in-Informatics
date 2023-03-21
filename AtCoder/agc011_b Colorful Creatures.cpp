#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e5;

int N;
lxl A[maxN + 10];
int ans = 0;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    std::sort(A + 1, A + N + 1);
    for (int i = 1; i <= N; i++) {
        A[i] += A[i - 1];
        ans++;
        if (A[i] * 2 < A[i + 1]) ans = 0;
    }
    std::cout << ans;
    return 0;
}
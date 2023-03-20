#include <iostream>
#include <cstring>

typedef char chr;
typedef long long lxl;

const int maxN = 2e5;

int N;
chr A[maxN + 10];
int C[maxN + 10];
lxl ans;

int main() {
    std::cin >> (A + 1);
    N = std::strlen(A + 1);
    for (int i = 1; i <= N; i++) C[A[i] - 'a' + 1]++;
    for (int i = 1; i <= N; i++) ans += 1ll * C[A[i] - 'a' + 1] * (N - C[A[i] - 'a' + 1]), C[A[i] - 'a' + 1] = 0;
    std::cout << ans / 2 + 1;
    return 0;
}
#include <iostream>

typedef char chr;

const int maxN = 1e5;
const int mod = 1e9 + 7;

int N;
chr S[maxN + 10];
int C[30];
int ans = 1;

int main() {
    std::cin >> N;
    std::cin >> (S + 1);
    for (int i = 1; i <= N; i++) C[S[i] - 'a' + 1]++;
    for (int i = 1; i <= 26; i++) ans = 1ll * ans * (C[i] + 1) % mod;
    std::cout << ans - 1;
    return 0;
}
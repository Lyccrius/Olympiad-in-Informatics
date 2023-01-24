#include <iostream>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 400;
const int maxS = 1000;

int N;
int S[maxN + 10], F[maxN + 10];
int f[maxN * maxS * 2 + 10];
int ans;

int main() {
    std::memset(f, 0xcf, sizeof(f));
    f[maxN * maxS] = 0;
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> S[i] >> F[i];
    for (int i = 1; i <= N; i++) {
        if (S[i] >= 0) {
            for (int j = maxN * maxS * 2; j >= S[i]; j--) {
                f[j] = std::max(f[j], f[j - S[i]] + F[i]);
            }
        } else {
            for (int j = 0; j <= maxN * maxS * 2 + S[i]; j++) {
                f[j] = std::max(f[j], f[j - S[i]] + F[i]);
            }
        }
    }
    for (int j = maxN * maxS; j <= maxN * maxS * 2; j++) {
        if (f[j] >= 0) {
            ans = std::max(ans, f[j] + j - maxN * maxS);
        }
    }
    std::cout << ans << '\n';
    return 0;
}
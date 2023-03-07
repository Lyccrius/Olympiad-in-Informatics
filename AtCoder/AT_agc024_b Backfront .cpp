#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int N;
int P[maxN + 10];
int Q[maxN + 10];
int F[maxN + 10];
int ans = maxN;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> P[i];
    for (int i = 1; i <= N; i++) Q[P[i]] = i;
    for (int i = 1; i <= N; i++) F[i] = 1;
    for (int i = 1; i <= N; i++) {
        if (Q[P[i] - 1] < Q[P[i]]) {
            F[P[i]] = F[P[i] - 1] + 1;
            ans = std::min(ans, N - F[P[i]]);
        }
    }
    std::cout << ans;
    return 0;
}
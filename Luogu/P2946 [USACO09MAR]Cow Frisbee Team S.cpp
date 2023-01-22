#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2000;
const int maxF = 1000;
const int mod = 1e8;

int N, F;
int R[maxN + 10];
int G[maxN + 10][maxF + 10];

int main() {
    promote();
    std::cin >> N >> F;
    //G[0][0] = 1;
    for (int i = 1; i <= N; i++) std::cin >> R[i], R[i] %= F;
    for (int i = 1; i <= N; i++) G[i][R[i]] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < F; j++) {
            G[i][j] = ((G[i][j] + G[i - 1][j]) % mod + G[i - 1][(j - R[i] + F) % F]) % mod;
        }
    }
    std::cout << G[N][0] << '\n';
    return 0;
}
#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 100;

int N, M;
int A, B;
int f[maxN + 10][maxN + 10];
int g[maxN + 10];
int h;

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= M; i++) std::cin >> A >> B, f[A][B] = true;
    for (int i = 1; i <= N; i++) f[i][i] = true;
    for (int k = 1; k <= N; k++) for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) f[i][j] |= f[i][k] && f[k][j];
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) if (f[i][j] || f[j][i]) g[i]++;
    for (int i = 1; i <= N; i++) if (g[i] == N) h++;
    std::cout << h << '\n';
    return 0;
}
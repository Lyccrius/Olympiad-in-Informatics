#include <iostream>

const int maxM = 12;
const int maxN = 12;
const int mod = 1e8;

int M, N;
int A[maxM + 10][maxN + 10];
int B[maxM + 10];
int F[maxM + 10][(1 << (maxN + 1)) + 10];
int ans;

bool check(int S, int T) {
    if (S & (S << 1)) return false;
    if (S & (S >> 1)) return false;
    if (S ^ (S & T)) return false;
    return true;
}

int main() {
    std::cin >> M >> N;
    for (int i = 1; i <= M; i++) for (int j = 1; j <= N; j++) std::cin >> A[i][j];
    for (int i = 1; i <= M; i++) for (int j = 1; j <= N; j++) B[i] = (B[i] << 1) + A[i][j];
    F[0][0] = 1;
    for (int i = 1; i <= M; i++) {
        for (int S1 = 0; S1 <= (1 << (N + 1)) - 1; S1++) if (check(S1, B[i - 1])) {
            for (int S2 = 0; S2 <= (1 << (N + 1)) - 1; S2++) if (check(S2, B[i])) {
                if (S1 & S2) continue;
                F[i][S2] = (F[i][S2] + F[i - 1][S1]) % mod;
            }
        }
    }
    for (int S = 0; S <= (1 << (N + 1)) - 1; S++) if (check(S, B[M])) ans = (ans + F[M][S]) % mod;
    std::cout << ans;
    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxK = 100;

int T;
int A, B, K;
vic C;
int F[20][maxK + 10][maxK + 10];

int DFS(int now, int num, int sum, int lim) {
    if (now == 0) return (num == 0) && (sum == 0);
    if (F[now][num][sum] >= 0 && !lim) return F[now][num][sum];
    int tot = 9;
    int ret = 0;
    if (lim) tot = C[now - 1];
    for (int i = 0; i <= tot; i++) ret += DFS(now - 1, (num * 10 + i) % K, (sum + i) % K, lim && (i == tot));
    if (!lim) F[now][num][sum] = ret;
    return ret;
}

int solve(int N) {
    C.clear();
    std::fill(F[0][0], F[0][0] + (20) * (maxK + 10) * (maxK + 10), -1);
    while (N) {
        C.push_back(N % 10);
        N /= 10;
    }
    return DFS(C.size(), 0, 0, 1);
}

void mian() {
    std::cin >> A >> B >> K;
    if (K > maxK) {
        std::cout << 0 << '\n';
    } else {
        std::cout << solve(B) - solve(A - 1) << '\n';
    }
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}
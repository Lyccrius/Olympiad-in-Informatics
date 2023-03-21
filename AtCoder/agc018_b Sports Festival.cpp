#include <iostream>
#include <algorithm>

const int maxN = 300;
const int maxM = 300;

int N, M;
int A[maxN + 10][maxM + 10];
int cur[maxN + 10];
int cnt[maxM + 10];
int vis[maxM + 10];
int pos;
int ans = maxN;

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) std::cin >> A[i][j];
    for (int i = 1; i <= N; i++) cur[i] = 1;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= M; j++) cnt[j] = 0; pos = 0;
        for (int j = 1; j <= N; j++) cnt[A[j][cur[j]]]++;
        for (int j = 1; j <= M; j++) if (cnt[j] > cnt[pos]) pos = j;
        vis[pos] = true; ans = std::min(ans, cnt[pos]);
        for (int j = 1; j <= N; j++) while (vis[A[j][cur[j]]]) cur[j]++;
    }
    std::cout << ans;
    return 0;
}
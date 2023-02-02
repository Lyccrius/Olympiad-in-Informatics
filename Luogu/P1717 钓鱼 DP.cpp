#include <iostream>
#include <algorithm>
#include <queue>

const int maxN = 25;
const int maxH = 16;
const int inf = 1e9;

int n;
int H;
int f[maxN + 10];
int d[maxN + 10];
int t[maxN + 10];

int dp[maxN + 10][maxH * 12 + 10];
int ans;

int main() {
    std::cin >> n;
    std::cin >> H;
    H *= 12;
    for (int i = 1; i <= n; i++) std::cin >> f[i];
    for (int i = 1; i <= n; i++) std::cin >> d[i];
    for (int i = 1; i < n; i++) std::cin >> t[i];
    std::fill(dp[0], dp[0] + (maxN + 10) * (maxH * 12 + 10), -inf);
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        //printf("i = %d\n", i);
        for (int j = 1; j <= H; j++) {
            //printf("j = %d\n", j);
            for (int k = 0; k <= j - t[i - 1]; k++) {
                //printf("k = %d\n", k);
                if ((k - 1) * d[i] < f[i]) {
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - t[i - 1] - k] + k * f[i] - k * (k - 1) / 2 * d[i]);
                    //printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
                    ans = std::max(ans, dp[i][j]);
                }
            }
        }
    }
    std::cout << ans;
    return 0;
}
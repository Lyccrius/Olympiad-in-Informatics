#include <bits/stdc++.h>

using namespace std;

int N, R;
int X, Y, W;
int S[5005][5005];

int main() {
    cin >> N >> R;

    R = min(R, 5001);

    int n = R, m = R;

    while (N --) {
        cin >> X >> Y >> W;
        S[++ X][++ Y] += W;
        n = max(n, X);
        m = max(m, Y);
    }

    for (int i = 1; i <= 5001; i ++) {
        for (int j = 1; j <= 5001; j ++) {
            S[i][j] += S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
        }
    }

    int ans = 0;

    for (int i = R; i <= 5001; i ++) {
        for (int j = R; j <= 5001; j ++) {
            ans = max(ans, S[i][j] - S[i - R][j] - S[i][j - R] + S[i - R][j - R]);
        }
    }

    cout << ans << endl;

    return 0;
}
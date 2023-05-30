#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 5000;
const int maxA = 1e6;
const int sqrA = 1e3;
const int mod = 998244353;

int n;
int a[maxN + 10];
int b[maxN + 10];
int A[maxN + 10];
vic pri;
int vis[maxA + 10];
int dec[maxA + 10][5];
int pre[sqrA + 10][sqrA + 10];

void init() {
    dec[1][1] = dec[1][2] = dec[1][3] = 1;
    for (int i = 2; i <= maxA; i++) {
        if (!vis[i]) {
            pri.push_back(i);
            dec[i][1] = dec[i][2] = 1;
            dec[i][3] = i;
        }
        for (auto j : pri) {
            if (i * j > maxA) break;
            vis[i * j] = true;
            int t1 = i * j;
            int t2 = dec[i][1] * j;
            if (t2 < dec[i][2]) {
                dec[t1][1] = t2;
                dec[t1][2] = dec[i][2];
                dec[t1][3] = dec[i][3];
            } else if (t2 < dec[i][3]) {
                dec[t1][1] = dec[i][2];
                dec[t1][2] = t2;
                dec[t1][3] = dec[i][3];
            } else {
                dec[t1][1] = dec[i][2];
                dec[t1][2] = dec[i][3];
                dec[t1][3] = t2;
            }
            if (i % j == 0) break;
        }
    }
    for (int i = 1; i <= sqrA; i++) {
        pre[0][i] = pre[i][0] = i;
        for (int j = 1; j <= i; j++) {
            pre[i][j] = pre[j][i] = pre[j][i % j];
        }
    }
    return;
}

int gcd(int a, int b) {
    if (a <= sqrA && b <= sqrA) return pre[a][b];
    int ret = 1;
    for (int i = 1; i <= 3; i++) {
        int d;
        if (dec[a][i] <= sqrA) d = pre[dec[a][i]][b % dec[a][i]];
        else if (b % dec[a][i] == 0) d = dec[a][i];
        else d = 1;
        b /= d;
        ret *= d;
    }
    return ret;
}

int main() {
    init();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) for (int j = 1, k = i; j <= n; j++, k = 1ll * k * i % mod) A[i] = (1ll * A[i] + 1ll * k * gcd(a[i], b[j]) % mod) % mod;
    for (int i = 1; i <= n; i++) std::cout << A[i] << '\n';
    return 0;
}
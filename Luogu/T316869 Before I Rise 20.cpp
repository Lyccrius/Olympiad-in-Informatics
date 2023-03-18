#include <iostream>
#include <algorithm>
#include <map>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::map<int, std::map<int, bool> > iib;

const int maxN = 2e5;
const int maxX = 1e5;
const int maxY = 1e5;

const int mod = 1e9 + 7;

int n, x, y;
int l[maxX + 10], r[maxX + 10];
int u[maxY + 10], d[maxY + 10];
iib srz;
iib sxc;

namespace SubTask {
    namespace _5 {
        bool is() {
            return n == 1;
        }

        void mian() {
            std::cout << 1;
            return;
        }
    }

    namespace _20 {
        bool is() {
            return n <= 10;
        }
        
        int a[maxN + 10];
        int v[maxN + 10];
        int ans;

        bool check() {
            for (int i = 1; i <= x; i++) {
                if (srz[a[l[i]]][a[r[i]]] == false) {
                    return false;
                }
            }
            for (int i = 1; i <= y; i++) {
                if (sxc[a[u[i]]][a[d[i]]] == false) {
                    return false;
                }
            }
            return true;
        }

        void DFS(int now) {
            if (now > n) {
                if (check()) ans++;
                return;
            }
            for (int i = 1; i <= n; i++) {
                if (v[i]) continue;
                a[now] = i;
                v[i] = true;
                DFS(now + 1);
                v[i] = false;
            }
            return;
        }

        void mian() {
            DFS(1);
            std::cout << ans << '\n';
            return;
        }
    }

    namespace _35 {
        int fac[maxN + 10];

        int pow(int a, int b) {
            int ret = 1 % mod;
            while (b) {
                if (b & 1) ret = 1ll * ret * a % mod;
                a = 1ll * a * a % mod;
                b = b / 2;
            }
            return ret;
        }

        void mian() {
            fac[0] = 1;
            for (int i = 1; i <= std::max(x, y); i++) {
                fac[i] = 1ll * fac[i - 1] * i % mod;
            }
            int ans = 1;
            if (pow(2, x)) ans = 1ll * ans * pow(2, x) % mod;
            if (pow(2, y)) ans = 1ll * ans * pow(2, x) % mod;
            if (fac[x]) ans = 1ll * ans * fac[x] % mod;
            if (fac[y]) ans = 1ll * ans * fac[y] % mod;
            std::cout << ans << '\n';
            return;
        }
    }
}

int main() {
    promote();
    //freopen("a2.in", "r", stdin);
    //freopen("a2.out", "w", stdout);
    std::cin >> n >> x >> y;
    for (int i = 1; i <= x; i++) {
        std::cin >> l[i] >> r[i];
        srz[l[i]][r[i]] = true;
        srz[r[i]][l[i]] = true;
    }
    for (int i = 1; i <= y; i++) {
        std::cin >> u[i] >> d[i];
        sxc[u[i]][d[i]] = true;
        sxc[d[i]][u[i]] = true;
    }
    if (SubTask::_5::is()) SubTask::_5::mian();
    else if (SubTask::_20::is()) SubTask::_20::mian();
    else SubTask::_35::mian();
    return 0;
}
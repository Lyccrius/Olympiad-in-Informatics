#include <iostream>

const int maxN = 1e6;
const int maxM = 1e6;

int t;
int n, m;
int S[maxN + 10][3];
int T[maxN + 10][3];

namespace brute {
    const int maxN = 10;
    const int maxM = 10;

    int a[maxN + 10];
    int b[maxN + 10];
    int c[maxM + 10];
    int res[(1 << maxN) + 10];
    int tmp;
    int cnt;
    int ans;

    bool check() {
        tmp = 0;
        for (int i = 1; i <= m; i++) c[i] = false;
        for (int i = 1; i <= n; i++) {
            if (c[b[i]]) return false;
            c[b[i]] = true;
            if (a[i] == b[i]) tmp++;
        }
        return true;
    }

    void show() {
        std::cout << "A: "; for (int i = 1; i <= n; i++) std::cout << a[i] << ' '; std::cout << '\n';
        std::cout << "B: "; for (int i = 1; i <= n; i++) std::cout << b[i] << ' '; std::cout << '\n';
        std::cout << "X: " << tmp << '\n';
        std::cout << '\n';
        return;
    }   

    void DFSB(int now) {
        if (now > n) {
            if (check()) {
                res[cnt] = std::min(res[cnt], tmp);
                //show();
            }
            return;
        }
        for (int i = 1; i <= T[now][0]; i++) {
            b[now] = T[now][i];
            DFSB(now + 1);
        }
        return;
    }

    void DFSA(int now) {
        if (now > n) {
            cnt++;
            DFSB(1);
            return;
        }
        for (int i = 1; i <= S[now][0]; i++) {
            a[now] = S[now][i];
            DFSA(now + 1);
        }
        return;
    }

    void main() {
        cnt = 0;
        ans = 0;
        for (int i = 1; i <= (1 << n); i++) res[i] = n + 1;
        DFSA(1);
        for (int i = 1; i <= cnt; i++) ans = std::max(ans, res[i]);
        if (ans == n + 1) ans = - 1;
        std::cout << ans << '\n';
        return;
    }
}

namespace A {
    bool Bis() {
        for (int i = 1; i < n; i++) {
            if (T[i][0] != 2) return false;
            if (T[i][1] > T[i][2]) std::swap(T[i][1], T[i][2]);
            if (T[i][1] != i) return false;
            if (T[i][2] != i + 1) return false;
        }
        if (T[n][0] != 2) return false;
        if (T[n][1] < T[n][2]) std::swap(T[n][1], T[n][2]);
        if (T[n][1] != n) return false;
        if (T[n][2] != 1) return false;
        return true;
    }

    bool is() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= S[i][0]; j++) {
                for (int k = 1; k <= T[i][0]; k++) {
                    if (S[i][j] == T[i][k]) return false;
                }
            }
        }
        return true;
    }

    int c[maxM + 10];
    int v[maxN + 10];
    int r[maxM + 10];
    
    bool check() {
        int cnt = 0;
        for (int i = 1; i <= m; i++) c[i] = false;
        for (int i = 1; i <= m; i++) r[i] = 0;
        for (int i = 1; i <= n; i++) v[i] = false;
        for (int i = 1; i <= n; i++) {
            if (T[i][0] == 2) continue;
            if (c[T[i][1]]) return false;
            c[T[i][1]] = true;
            v[i] = true;
            cnt++;
        }
        for (int i = 1; i <= n; i++) {
            if (v[i]) continue;
            if (c[T[i][1]] && c[T[i][2]]) {
                return false;
            }
            if (c[T[i][1]] == c[T[i][2]]) {
                continue;
            }
            if (c[T[i][1]]) {
                c[T[i][2]] = true;
            } else {
                c[T[i][1]] = true;
            }
            v[i] = true;
            cnt++;
        }
        for (int i = 1; i <= n; i++) {
            if (v[i]) continue;
            r[T[i][1]]++;
            r[T[i][2]]++;
        }
        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= n; i++) {
                if (v[i]) continue;
                if (r[T[i][1]] == 1) {
                    c[T[i][1]] = true;
                    v[i] = true;
                    cnt++;
                    r[T[i][1]]--;
                    r[T[i][2]]--;
                } else if (r[T[i][2]] == 1) {
                    c[T[i][2]] = true;
                    v[i] = true;
                    cnt++;
                    r[T[i][1]]--;
                    r[T[i][2]]--;
                }
            }
            if (cnt == n) return true;
        }
        return false;
    }

    void main() {
        if (check()) {
            std::cout << 0 << '\n';
        } else {
            std::cout << -1 << '\n';
        }
        return;
    }
}

void mian() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> S[i][0];
        for (int j = 1; j <= S[i][0]; j++) {
            std::cin >> S[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> T[i][0];
        for (int j = 1; j <= T[i][0]; j++) {
            std::cin >> T[i][j];
        }
    }
    //if (A::is()) A::main();
    //if (n <= 10 && m <= 10) 
    brute::main();
    return;
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    std::cin >> t;
    while (t--) mian();
    return 0;
}
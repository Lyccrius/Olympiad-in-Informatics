#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000 + 10;

int n, R;

int fa[maxn], nxt[maxn], lst[maxn], num[maxn];
double c[maxn], d[maxn], tot[maxn];
bool v[maxn];

int main() {
    cin >> n >> R;

    for (int i = 1; i <= n; i ++) {
        cin >> c[i];

        nxt[i] = i;
        lst[i] = i;
        num[i] = 1;
        tot[i] = c[i];
    }

    memcpy(d, c, sizeof(d));

    for (int i = 1; i < n; i ++) {
        int a, b;

        cin >> a >> b;

        fa[b] = a;
    }

    memset(v, 0, sizeof(v));

    for (int i = 1; i < n; i ++) {
        int p;
        double k = 0;

        for (int j = 1; j <= n; j ++) {
            if (j != R && !v[j] && c[j] > k) {
                k = c[j];
                p = j;
            }
        }
            
        int f = fa[p];

        while (v[f]) {
          fa[p] = f = fa[f];
        }

        nxt[lst[f]] = p;
        lst[f] = lst[p];
        num[f] += num[p];
        tot[f] += tot[p];
        c[f] = tot[f] / num[f];
        v[p] = 1;
    }

    int ans = 0;

    for (int i = 1; i <= n; i ++) {
        ans += i * d[R];
        R = nxt[R];
    }

    cout << ans << endl;

    return 0;
}
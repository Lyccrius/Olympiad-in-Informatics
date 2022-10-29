#include <bits/stdc++.h>

using namespace std;

int n, m;
int a[200010];
int b[200010];
int c[200010];

int lan[600010], tot;
int uni[600010], cnt;
int num[600010];

int query(int x) {
    return lower_bound(uni + 1, uni + cnt + 1, x) - uni;
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        lan[++ tot] = a[i];
    }

    cin >> m;

    for (int i = 1; i <= m; i ++) {
        cin >> b[i];
        lan[++ tot] = b[i];
    }

    for (int i = 1; i <= m; i ++) {
        cin >> c[i];
        lan[++ tot] = c[i];
    }

    sort(lan + 1, lan + tot + 1);

    for (int i = 1; i <= tot; i ++) {
        if (i == 1 || lan[i] != lan[i - 1]) {
            uni[++ cnt] = lan[i];
        }
    }

    for (int i = 1; i <= n; i ++) {
        num[query(a[i])] ++;
    }

    int ans, voi = -1, sub = -1;

    for (int i = 1; i <= m; i ++) {
        if (voi < num[query(b[i])] || (voi == num[query(b[i])] && sub < num[query(c[i])])) {
            ans = i;
            voi = num[query(b[i])];
            sub = num[query(c[i])];
        }
    }

    cout << ans << endl;

    return 0;
}
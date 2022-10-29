#include <bits/stdc++.h>

const int maxn = 5e5 + 10;

int n;
long long a[maxn];

int s;
long long bel[maxn];
long long tag[maxn];
long long sum[maxn];

void add(int l, int r, long long x) {
    int sbl = bel[l];
    int ebl = bel[r];

    if (sbl == ebl) {
        for (int i = l; i <= r; i++) {
            a[i] += x;
            sum[sbl] += x;
        }

        return;
    }

    for (int i = l; bel[i] == sbl; i++) {
        a[i] += x;
        sum[sbl] += x;
    }

    for (int i = sbl + 1; i < ebl; i++) {
        tag[i] += x;
        sum[i] += s * x;
    }

    for (int i = r; bel[i] == ebl; i--) {
        a[i] += x;
        sum[ebl] += x;
    }

    return;
}

long long query(int l, int r, long long mod) {
    int sbl = bel[l];
    int ebl = bel[r];

    long long ans = 0;

    if (sbl == ebl) {
        for (int i = l; i <= r; i++) {
            ans = (ans + a[i] + tag[sbl]) % mod;
        }

        return ans;
    }

    for (int i = l; bel[i] == sbl; i++) {
        ans = (ans + a[i] + tag[sbl]) % mod;
    }

    for (int i = sbl + 1; i < ebl; i++) {
        ans = (ans + sum[i]) % mod;
    }

    for (int i = r; bel[i] == ebl; i--) {
        ans = (ans + a[i] + tag[ebl]) % mod;
    }

    return ans;
}

int main() {
    scanf("%d", &n);
    s = sqrt(n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        bel[i] = (i - 1) / s + 1;
        sum[bel[i]] += a[i];
    }

    int opt, l, r, c;

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &opt, &l, &r, &c);

        if (opt) {
            printf("%lld\n", query(l, r, c + 1));
        } else {
            add(l, r, c);
        }
    }

    return 0;
}
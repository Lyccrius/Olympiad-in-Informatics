#include <bits/stdc++.h>

using namespace std;

int n, m;

char opt[5];

int t;

pair<string, int> a[100010];

int cal(int bit, int now) {
    for (int i = 1; i <= n; i ++) {
        int x = (a[i].second >> bit) & 1;

        if (a[i].first == "AND") now &= x;
        else if (a[i].first == "OR") now |= x;
        else now ^= x;
    }

    return now;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        cin >> opt >> t;

        a[i] = make_pair(opt, t);
    }

    int val = 0, ans = 0;

    for (int bit = 29; bit >= 0; bit --) {
        int res0 = cal(bit, 0);
        int res1 = cal(bit, 1);

        if (val + (1 << bit) <= m && res0 < res1) {
            val += 1 << bit;
            ans += res1 << bit;
        }else{
            ans += res0 << bit;
        }
    }

    cout << ans << endl;

    return 0;
}
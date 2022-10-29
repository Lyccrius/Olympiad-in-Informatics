#include <bits/stdc++.h>

using namespace std;

struct node {
    int l;
    int r;

    bool operator < (node x) const {
        return l < x.l;
    }
};

int n;

node section[100010];

int ans = 0;

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++) cin >> section[i].l >> section[i].r;

    sort(section + 1, section + 1 + n);

    int last = -0x7f7f7f7f;

    for (int i = 1; i <= n; i ++) {
        if (section[i].l <= last) last = max(last, section[i].r);
        else {
            last = section[i].r;
            ans ++;
        }
    }

    cout << ans << endl;

    return 0;
}
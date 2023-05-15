#include <bits/stdc++.h>

using namespace std;

typedef long long lxl;

int n;
int a[500010];
lxl op;

void merge(int l, int r) {
    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;

    merge(l, mid);
    merge(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    int tmp[500010];

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k ++] = a[i ++];
        } else {
            tmp[k ++] = a[j ++];
            op += mid - i + 1;
        }
    }

    while (i <= mid) {
        tmp[k ++] = a[i ++];
    }

    while (j <= r) {
        tmp[k ++] = a[j ++];
    }

    for (int i = l; i <= r; i ++) {
        a[i] = tmp[i];
    }

    return;
}

int main() {
    while (cin >> n && n) {
        for (int i = 1; i <= n; i ++) {
            cin >> a[i];
        }

        op = 0;
        merge(1, n);

        cout << op << endl;
    }

    return 0;
}
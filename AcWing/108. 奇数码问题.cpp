#include <bits/stdc++.h>

using namespace std;

int n;
int a[250010];
int b[250010];

long long merge(int x[], int l, int r) {
    if (l >= r) {
        return 0;
    }

    int mid = (l + r) >> 1;
    long long res = merge(x, l, mid) + merge(x, mid + 1, r);

    int i = l, j = mid + 1, k = l;
    int tmp[250010];

    while (i <= mid && j <= r) {
        if (x[i] <= x[j]) {
            tmp[k ++] = x[i ++];
        } else {
            tmp[k ++] = x[j ++];
            res += mid - i + 1;
        }
    }

    while (i <= mid) {
        tmp[k ++] = x[i ++];
    }

    while (j <= r) {
        tmp[k ++] = x[j ++];
    }

    for (int i = l; i <= r; i ++) {
        x[i] = tmp[i];
    }

    return res;
}

int main() {
    while (cin >> n) {
        int m = n * n - 1;

        for (int i = 0, k = 0; i <= m; i ++) {
            cin >> a[0];

            if (a[0]) {
                a[++ k] = a[0];
            }
        }

        for (int i = 0, k = 0; i <= m; i ++) {
            cin >> b[0];

            if (b[0]) {
                b[++ k] = b[0];
            }
        }

        long long ans = merge(a, 1, m) ^ merge(b, 1, m);
        
        
        if (ans & 1) {
            cout << "NIE" << endl;
        } else {
            cout << "TAK" << endl;
        }
    }

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

int n;

long long a[100010];
long long b[100010];

int main() {
    cin >> n;

    long long p = 0, q = 0;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        b[i] = a[i] - a[i - 1];

        if (i != 1) {
            if (b[i] > 0) {
                p += b[i];
            } else {
                q -= b[i];
            }
        }
        
    }

    cout << max(p, q) << endl;
    cout << max(p, q) - min(p, q) + 1 << endl;

    return 0;
}
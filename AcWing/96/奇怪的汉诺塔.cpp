#include <bits/stdc++.h>

using namespace std;

int n;

int d[20];
int f[20];

int main() {
    for (int x = 1; x <= 12; x ++) {
        for (int i = 1; i <= x; i ++) d[i] = 2 * d[i - 1] + 1;

        memset(f, 0x3f, sizeof(f));
        f[1] = 1;

        for (int i = 2; i <= x; i ++) {
            for (int j = 1; j < x; j ++) {
                f[i] = min(f[i], 2 * f[j] + d[i - j]);
            }
        }

        cout << f[x] << endl;
    }

    return 0;
}
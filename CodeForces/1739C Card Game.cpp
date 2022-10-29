#include <bits/stdc++.h>
 
using namespace std;
 
const int mod = 998244353;
 
int T;
 
int n;
 
long long c[110][110];
long long a[110], b[110], t[110];
 
int main() {
    for (int i = 0; i <= 110; i++) {
        c[i][0] = 1;
        c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
        }
    }

    a[2] = 1;
    b[2] = 0;
    t[2] = 1;

    for (int i = 4; i <= 110; i += 2){
        t[i] = 1;
        a[i] = (c[i - 2][(i / 2) - 2] + c[i - 2][(i - 2) / 2] + b[i - 2]) % mod;
        b[i] = ((c[i][i / 2] - a[i] - 1) % mod + mod) % mod;
    }
 
    cin >> T;
 
    while (T--) {
        cin >> n;
 
        cout << a[n] << " " << b[n] << " " << t[n] << endl;
    }
 
    return 0;
}
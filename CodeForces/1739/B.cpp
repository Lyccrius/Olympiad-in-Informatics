#include <bits/stdc++.h>
 
using namespace std;
 
int t;
 
int n;
int a[110];
int d[110];
 
int main() {
    cin >> t;
 
    while (t --) {
        memset(a, 0, sizeof(a));
 
        cin >> n;
 
        bool flag = true;
 
        for (int i = 1; i <= n; i ++) {
            cin >> d[i];
 
            if (d[i] && d[i] <= a[i - 1]) {
                flag = false;
            }
 
            a[i] = a[i - 1] + d[i];
        }
 
        if (flag) {
            for (int i = 1; i <= n; i ++) {
                cout << a[i] << " ";
            }
        } else {
            cout << -1;
        }
 
        cout << endl;
    }
 
    return 0;
}
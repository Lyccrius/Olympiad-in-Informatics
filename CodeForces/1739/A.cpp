#include <bits/stdc++.h>
 
using namespace std;
 
int t;
 
int n, m;
 
int main() {
    cin >> t;
 
    while (t --) {
        cin >> n >> m;
 
        cout << ((n + 1) >> 1) << " " << ((m + 1) >> 1) << endl;
    }
 
    return 0;
}
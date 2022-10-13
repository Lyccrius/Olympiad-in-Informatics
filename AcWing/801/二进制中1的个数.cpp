#include <bits/stdc++.h>

using namespace std;

int n, i;

int main() {
    cin >> n;

    while (n --) {
        int cnt = 0;

        cin >> i;

        while (i) {
            if (i & 1) cnt ++;
            i >>= 1;
        }

        cout << cnt << " ";
    }

    cout << endl;

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

int n;

int a0, a1;

int b0, b1;

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int main() {
    cin >> n;

    while (n --) {
        cin >> a0 >> a1 >> b0 >> b1;

        int ans = 0;

        for (int i = 1; i * i <= b1; i ++) {
            int x = i;
            
            if (b1 % x != 0) continue;

            if ((x % a1 == 0) && (b1 % x == 0) && (gcd(x / a1, a0 / a1) == 1) && (gcd(b1 / b0, b1 / x) == 1)) ans ++; 

            if (x == b1 / i) continue;
            x = b1 / i;

            if ((x % a1 == 0) && (b1 % x == 0) && (gcd(x / a1, a0 / a1) == 1) && (gcd(b1 / b0, b1 / x) == 1)) ans ++; 
        }

        cout << ans << endl;
    }

    return 0;
}
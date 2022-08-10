#include <bits/stdc++.h>

using namespace std;

int match[1010] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int n;

int main() {
    cin >> n;

    for (int i = 10; i <= 1000; i ++) match[i] = match[i / 10] + match[i % 10];

    int ans = 0;

    for (int A = 0; A <= 1000; A ++) {
        for (int B = 0; A + B <= 1000; B ++) {
            int C = A + B;

            if (match[A] + match[B] + match[C] + 4 == n) ans ++;
        }
    }

    cout << ans << endl;

    return 0;
}
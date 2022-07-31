#include <bits/stdc++.h>

using namespace std;

int A, B;

int S = 1;

const int mod = 9901;

int pow(int a, int b) {
    int ans = 1;

    while (b) {
        if (b & 1) ans = (long long)ans * a % mod;
        a = (long long)a * a % mod;
        b >>= 1;
    }

    return ans;
}

int sum(int p, int c) {
    if (! c) return 1;

    if (c & 1) return (1 + pow(p, (c + 1) / 2)) * sum(p, (c - 1) / 2) % mod;
    else return ((1 + pow(p, c / 2)) * sum(p, c / 2 - 1) + pow(p, c)) % mod;
}

int main() {
    cin >> A >> B;

    for (int p = 2; p <= A; p ++) {
        int c = 0;

        while (A % p == 0) {
            c ++;
            A /= p;
        }

        if (c)  S = S * sum(p, B * c) % mod;
    }

    cout << (A ? S : 0) << endl;

    return 0;
}
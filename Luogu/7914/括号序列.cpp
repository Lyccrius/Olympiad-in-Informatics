#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

long long n, k;
char s[510] = " ";
long long S[510][510], A[510][510], _A[510][510], S_A[510][510];

bool isl(char x) {
    return x == '(' || x == '?';
}

bool isr(char x) {
    return x == ')' || x == '?';
}

bool isx(char x) {
    return x == '*' || x == '?';
}


int main() {
    cin >> n >> k >> s + 1;

    for (int l = 1; l <= n; l ++) {
        if (!isx(s[l])) {
            continue;
        }
        S[l][l] = 1;

        for (int r = l + 1; r <= min(n, l + k - 1); r ++) {
            if (!isx(s[r])) {
                break;
            }
            S[l][r] = 1;
        }
    }

    for (int l = n - 1; l >= 1; l --) {
        for (int r = l + 1; r <= n; r ++) {
            if (r - l == 1) {
                if (isl(s[l]) && isr(s[r])) {
                    A[l][r] = 1;
                    _A[l][r] = 1;
                }
                continue;
            }
            if (isl(s[l]) && isr(s[r])) {
                A[l][r] = (A[l][r] + S[l + 1][r - 1]) % mod;
                A[l][r] = (A[l][r] + A[l + 1][r - 1]) % mod;
                for (int i = l + 1; i < r - 1; i ++) {
                    A[l][r] = (A[l][r] + S[l + 1][i] * A[i + 1][r - 1]) % mod;
                }
                for (int i = l + 1; i < r - 1; i ++) {
                    A[l][r] = (A[l][r] + A[l + 1][i] * S[i + 1][r - 1]) % mod;
                }
            }

            _A[l][r] = A[l][r];

            for (int i = l; i < r; i ++) {
                S_A[l][r] = (S_A[l][r] + S[l][i] * _A[i + 1][r]) % mod;
            }

            for (int i = l; i < r; i ++) {
                A[l][r] = (A[l][r] + A[l][i] * _A[i + 1][r]) % mod;
            }

            for (int i = l; i < r; i ++) {
                A[l][r] = (A[l][r] + A[l][i] * S_A[i + 1][r]) % mod;
            }
        }
    }

    cout << A[1][n] << endl;

    return 0;
}
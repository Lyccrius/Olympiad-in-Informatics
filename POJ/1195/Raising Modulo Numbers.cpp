#include <iostream>

using namespace std;

int Z;

int M, H;

int A, B;

int pow(int a, int b, int mod) {
    int ans = 1 % mod;

    while (b) {
        if (b & 1) ans = (long long)ans * a % mod;
        a = (long long)a * a % mod;
        b >>= 1;
    }
   
    return ans;
}

int main() {
    cin >> Z;

    while (Z --) {
        int ans = 0;

        cin >> M >> H;

        while (H --) {
            cin >> A >> B;

            ans = (ans + pow(A, B, M)) % M;
        }

        cout << ans << endl;
    }

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

int a, b, p;

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
	cin >> a >> b >> p;

    int ans = pow(a, b, p);
	
	cout << ans << endl;
	
	return 0;
}
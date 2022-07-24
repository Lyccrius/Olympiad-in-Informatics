#include <bits/stdc++.h>

using namespace std;

int a, b, p;

int fast_pow(int a, int b, int p) {
    int ans = 1 % p;
    
    while (b) {
        if (b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
        b >>= 1;
    }
    
    return ans;
}

int main() {
	cin >> a >> b >> p;
	
	cout << fast_pow(a, b, p) << endl;
	
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

long long a, b, p;

long long ans;

long long mul(long long a, long long b, long long p) {
    long long ans = 0;
    
    while (b) {
        if (b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
        b >>= 1;
    }
    
    return ans;
}

int main() {
	cin >> a >> b >> p;
	
    ans = mul(a, b, p);

	cout << ans << endl;
	
	return 0;
}
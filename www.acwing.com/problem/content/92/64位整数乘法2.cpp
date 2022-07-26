#include <bits/stdc++.h>

using namespace std;

long long a, b, p;

unsigned long long ans;

unsigned long long mul(unsigned long long a, unsigned long long b, unsigned long long p) {
    a %= p;
    b %= p;
    
    unsigned long long c = (long double)a * b / p;
    unsigned long long x = a * b;
    unsigned long long y = c * p;
    
    long long ans = (long long)(x % p) - (long long)(y % p);
    
    if (ans < 0) ans += p;
    
    return ans;
}

int main() {
	cin >> a >> b >> p;

    ans = mul(a, b, p);
	
	cout << ans << endl;
	
	return 0;
}
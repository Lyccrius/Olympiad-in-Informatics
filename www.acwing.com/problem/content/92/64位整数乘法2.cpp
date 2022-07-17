#include <bits/stdc++.h>

using namespace std;

long long a, b, p;

unsigned long long c, x, y;

long long ans;

int main() {
	cin >> a >> b >> p;
	
	c = (long double)a * b / p;
	x = a * b;
	y = c * p;
	
	ans = (long long)(x % p) - (long long)(y % p);
	
	if (ans < 0) ans += p;
	
	cout << ans << endl;
	
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

long long a, b, p;

long long ans;

int main() {
	cin >> a >> b >> p;
	
	for (; b; b >>= 1) {
		if (b & 1) ans = (ans + a) % p;
		a = a * 2 % p;
	}
	
	cout << ans << endl;
	
	return 0;
}
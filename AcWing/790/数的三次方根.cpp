#include <bits/stdc++.h>

using namespace std;

double n;

double l = -10000, r = 10000;
double mid;

int main() {
	cin >> n;
	
	while (r - l >= 1e-8) {
		mid = (l + r) / 2;
		
		if (mid * mid * mid > n) r = mid;
		else l = mid;
	}
	
	printf("%lf\n", mid);
	
	return 0;
}
#include <iostream>

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
	
	printf("%d^%d mod %d=%d\n", a, b, p, fast_pow(a, b, p));
	
	return 0;
}
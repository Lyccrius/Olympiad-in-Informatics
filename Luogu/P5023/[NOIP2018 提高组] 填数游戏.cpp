#include <cstdio>
#include <iostream>

const int mod = 1e9 + 7;

int n,m;

int table[10][10] = {
	{0, 0, 0, 0, 0, 0, 0},
	{0, 2, 4},
	{0, 0, 12, 36},
	{0, 0, 0, 112, 336},
	{0, 0, 0, 0, 912, 2688},
	{0, 0, 0, 0, 0, 7136, 21312},
	{0, 0, 0, 0, 0, 0, 56768, 170112},
	{0, 0, 0, 0, 0, 0, 0, 453504, 1360128},
	{0, 0, 0, 0, 0, 0, 0, 0, 3626752, 10879488}
};

long long pow(long long x, long long a) {
	long long ans = 1;

	while (a) {
		if (a & 1) {
            ans = ans * x %mod;
        }

		x = x * x % mod;
		a = a >> 1;
	}

	return ans;
}

int main() {
	scanf("%d", &n);
    scanf("%d", &m);

	if (n > m) {
        std::swap(n,m);
    }

	if (n == 1) {
		printf("%lld\n", pow(2, m));
        return 0;
	} 
    
    if (m - n <= 1) {
		printf("%d\n", table[n][m]);
	} else {
		printf("%lld\n", table[n][n + 1] * pow(3, m - n - 1) % mod);
	}

	return 0;
}
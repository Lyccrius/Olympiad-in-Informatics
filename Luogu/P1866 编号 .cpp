#include <cstdio>
#include <algorithm>

const int maxN = 50 + 10;
const int mod = 1000000007;

int n;
int Maxnumber[maxN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &Maxnumber[i]);
	std::sort(Maxnumber + 1, Maxnumber + n + 1);
	long long res = 1;
	for (int i = 1; i <= n; i++) res = (res * (Maxnumber[i] - i + 1)) % mod;
	printf("%lld\n", res);
	return 0;
}
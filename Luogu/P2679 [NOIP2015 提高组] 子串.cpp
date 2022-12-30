#include <cstdio>

const int maxN = 1000 + 10;
const int maxM = 200 + 10;
const int mod = 1e9 + 7;

long long n, m, k;
char A[maxN];
char B[maxM];
long long f[maxM][maxM];
long long s[maxM][maxM];

int main() {
    f[0][0] = 1;
	scanf("%lld%lld%lld", &n, &m, &k);
	scanf("%s%s", A, B);
    for (int i = 1; i <= n; i++) for (int j = m; j >= 1; j--) for (int l = k; l >= 1; l--) {
        if (A[i - 1] == B[j - 1]) s[j][l] = (s[j - 1][l] + f[j - 1][l - 1]) % mod;
        else s[j][l] = 0;
        f[j][l] = (f[j][l] + s[j][l]) % mod;
    }
    printf("%lld\n", f[m][k]);
	return 0;
}
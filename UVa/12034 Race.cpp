#include <iostream>

const int maxN = 1000;
const int mod = 10056;

int T;
int n;
int c[maxN + 10][maxN + 10];
int f[maxN + 10];

int main() {
	//c[1][1] = 1;
	f[0] = 1;
	for (int i = 1; i <= maxN; i++) c[i][0] = 1, c[i][i] = 1;
	for (int i = 1; i <= maxN; i++) for (int j = 1; j < i; j++) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];//, printf("c[%d][%d] = %d\n", i, j, c[i][j]);
	for (int i = 1; i <= maxN; i++) for (int j = 1; j <= i; j++) f[i] = (f[i] + c[i][j] * f[i - j] % mod) % mod;
	std::cin >> T;
	for (int kase = 1; kase <= T; kase++) {
		std::cin >> n;
		std::cout << "Case " << kase << ": " << f[n] << '\n';
	}
	return 0;
}
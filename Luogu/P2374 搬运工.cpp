#include <iostream>

typedef long long lxl;

const int maxN = 100;

int a[maxN + 10], b[maxN + 10], c[maxN + 10];
lxl f[maxN + 10][maxN + 10][maxN + 10];

int main() {
	std::cin >> a[0] >> b[0] >> c[0];
	for (int i = 1; i <= a[0]; i++) std::cin >> a[i];
	for (int i = 1; i <= b[0]; i++) std::cin >> b[i];
	for (int i = 1; i <= c[0]; i++) std::cin >> c[i];
	for (int i = 0; i <= a[0]; i++) {
		for (int j = 0; j <= b[0];j++) {
			for (int k = 0; k <= c[0]; k++) {
				lxl t = i + j + k;
				if (i > 0) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k] + t * a[a[0] - i + 1]);
				if (j > 0) f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][k] + t * b[b[0] - j + 1]);
				if (k > 0) f[i][j][k] = std::max(f[i][j][k], f[i][j][k - 1] + t * c[c[0] - k + 1]);
			}
		}
	}
	std::cout << f[a[0]][b[0]][c[0]];
    return 0;
}
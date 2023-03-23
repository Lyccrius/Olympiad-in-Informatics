#include <iostream>
#include <algorithm>

const int maxC = 100;
const int maxS = 1000;
const int maxQ = 10000;
const int inf = 1e9 + 10;

int kase;
int C, S, Q;
int c1, c2, d;
int f[maxC + 10][maxC + 10];

void mian() {
    if (kase) std::cout << '\n';
	std::cout << "Case #" << ++kase << '\n';
	//std::cin >> C >> S >> Q;
	for (int i = 1; i <= C; i++) for (int j = 1; j <= C; j++) f[i][j] = inf;
	for (int i = 1; i <= C; i++) f[i][i] = 0;
	for (int i = 1; i <= S; i++) {
		std::cin >> c1 >> c2 >> d;
		f[c1][c2] = std::min(f[c1][c2], d);
		f[c2][c1] = std::min(f[c2][c1], d);
	}
	for (int k = 1; k <= C; k++) {
		for (int i = 1; i <= C; i++) {
			for (int j = 1; j <= C; j++) {
				if (k == i) continue;
				if (k == j) continue;
				if (i == j) continue;
				f[i][j] = std::min(f[i][j], std::max(f[i][k], f[k][j]));
			}
		}
	}
	for (int i = 1; i <= Q; i++) {
		std::cin >> c1 >> c2;
		if (f[c1][c2] >= inf) {
			std::cout << "no path" << '\n';
		} else {
			std::cout << f[c1][c2] << '\n';
		}
	}
	//std::cout << '\n';
	return;
}

int main() {
	while (std::cin >> C >> S >> Q && C && S && Q) mian();
	return 0;
}
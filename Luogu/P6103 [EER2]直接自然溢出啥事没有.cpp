#include <iostream>

typedef unsigned long long lxl;

const int maxN = 1e4;

int n;
lxl f[maxN + 10][5];

int main(){
	std::cin >> n;
	f[0][1] = f[1][0] = f[1][1] = 1;
	for (int i = 2; i <= n; ++i) {
		f[i][3] = f[i - 2][2] + f[i - 2][3];
		if(i >= 4) f[i][3] += f[i - 4][2];
		f[i][2] = f[i - 2][1];
		f[i][0] = f[i][2] + f[i - 1][4];
		f[i][4] = f[i][3] + f[i - 2][4];
		for (int j = 0; j < i; ++j) f[i][1] += f[j][1] * f[i - j][0];
	}
    std::cout << f[n][1];
	return 0;
}
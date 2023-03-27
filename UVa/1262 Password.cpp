#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef char chr;
typedef std::vector<chr> vcc;
typedef std::map<chr, bool> mcb;

const int maxN = 6;
const int maxM = 5;

int t;
int n = 6;
int m = 5;
int k;
chr a[maxN + 10][maxM + 10];
chr b[maxN + 10][maxM + 10];
mcb appearA[maxM + 10];
mcb appearB[maxM + 10];
vcc reserve[maxM + 10];

void solve(int col, int tot) {
	//printf("solve(%d, %d)\n", col, tot);
	if (col > m) {
		std::cout << '\n';
		return;
	}
	tot /= reserve[col].size();
	std::cout << reserve[col][k / tot];
	k %= tot;
	solve(col + 1, tot);
	return;
}

void mian() {
	for (int i = 1; i <= m; i++) appearA[i].clear();
	for (int i = 1; i <= m; i++) appearB[i].clear();
	for (int i = 1; i <= m; i++) reserve[i].clear();
	std::cin >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			std::cin >> a[i][j];
			appearA[j][a[i][j]] = true;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			std::cin >> b[i][j];
			appearB[j][b[i][j]] = true;
		}
	}
	for (int j = 1; j <= m; j++) {
		for (chr ch = 'A'; ch <= 'Z'; ch++) {
			if (appearA[j][ch] && appearB[j][ch]) {
				reserve[j].push_back(ch);
			}
		}
	}
	int tot = 1;
	for (int j = 1; j <= m; j++) std::sort(reserve[j].begin(), reserve[j].end());
	for (int j = 1; j <= m; j++) tot *= reserve[j].size();
	if (k > tot) {
		std::cout << "NO" << '\n';
		return;
	}
	k--;
	solve(1, tot);
	return;
}

int main() {
	int t;
	std::cin >> t;
	while (t--) mian();
	return 0;
}
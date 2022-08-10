#include <bits/stdc++.h>

using namespace std;

int n, m, q;

int num[1010][1010];
int dif[1010][1010];

int x1, yy;
int x2, y2;
int c;

int main() {
	cin >> n >> m >> q;
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			cin >> num[i][j];
			dif[i][j] += num[i][j];
			dif[i + 1][j] -= num[i][j];
			dif[i][j + 1] -= num[i][j];
			dif[i + 1][j + 1] += num[i][j];
		}
	}
	
	while (q --) {
		cin >> x1 >> yy;
		cin >> x2 >> y2;
		cin >> c;
		dif[x1][yy] += c;
		dif[x2 + 1][yy] -= c;
		dif[x1][y2 + 1] -= c;
		dif[x2 + 1][y2 + 1] += c;
	}
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++ ) {
			dif[i][j] += dif[i - 1][j] + dif[i][j -1] - dif[i - 1][j - 1];
			cout << dif[i][j] << " ";
		}
		cout << endl;
	}
	
	return 0;
}
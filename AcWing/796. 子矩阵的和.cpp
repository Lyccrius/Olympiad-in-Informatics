#include <bits/stdc++.h>

using namespace std;

int n, m, q;

int num[1010][1010];
int pre[1010][1010];

int x1, yy;
int x2, y2;

int main() {
	cin >> n >> m >> q;
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			cin >> num[i][j];
			pre[i][j] = pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1] + num[i][j];
		}
	}
	
	while (q --) {	
		cin >> x1 >> yy;
		cin >> x2 >> y2;
		cout << pre[x2][y2] - pre[x1-1][y2] - pre[x2][yy-1] + pre[x1-1][yy-1] << endl;
	}
	
	return 0;
}
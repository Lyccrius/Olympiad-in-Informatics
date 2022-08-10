#include <bits/stdc++.h>

using namespace std;

int cnt;
int tree[500010];
int mx[500010][5];
int mn[500010][5];
void read() {
	char c;
	cin >> c;
	tree[++ cnt] = c - '0';

	if (tree[cnt] == 0) return;
	if (tree[cnt] == 1) {
		read();
		return;
	}
	if (tree[cnt] == 2) {
		read();
		read();
		return;
	}

	return;
}

void DFS(int base) {
	switch (tree[base]) {
		case 0: {
			mx[base][0] = 1;
			mn[base][0] = 1;
			break;
		}
		case 1: {
			DFS(++cnt);
			mx[base][0] = max(mx[base + 1][1], mx[base + 1][2]) + 1;
			mx[base][1] = max(mx[base + 1][0], mx[base + 1][2]);
			mx[base][2] = max(mx[base + 1][0], mx[base + 1][1]);
			mn[base][0] = min(mn[base + 1][1], mn[base + 1][2]) + 1;
			mn[base][1] = min(mn[base + 1][0], mn[base + 1][2]);
			mn[base][2] = min(mn[base + 1][0], mn[base + 1][1]);
			break;
		}
		case 2: {
			DFS(++cnt);
			int l = base + 1, r = cnt + 1;
			DFS(++cnt);
			mx[base][0] = max(mx[l][1] + mx[r][2], mx[l][2] + mx[r][1]) + 1;
			mx[base][1] = max(mx[l][0] + mx[r][2], mx[l][2] + mx[r][0]);
			mx[base][2] = max(mx[l][0] + mx[r][1], mx[l][1] + mx[r][0]);
			mn[base][0] = min(mn[l][1] + mn[r][2], mn[l][2] + mn[r][1]) + 1;
			mn[base][1] = min(mn[l][0] + mn[r][2], mn[l][2] + mn[r][0]);
			mn[base][2] = min(mn[l][0] + mn[r][1], mn[l][1] + mn[r][0]);
			break;
		}
	}

	return;
}

int main() {
	read();

	cnt = 0;

	DFS(++ cnt);

	cout << mx[1][0] << " " << min(mn[1][0], min(mn[1][1], mn[1][2])) << endl;

	return 0;
}
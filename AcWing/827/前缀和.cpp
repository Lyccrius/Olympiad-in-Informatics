#include <bits/stdc++.h>

using namespace std;

int n, m;

int num[100010];
int pre[100010];

int l, r;

int main() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i ++) {
		cin >> num[i];
		pre[i] = pre[i-1] + num[i];
	}
	
	while (m --) {
		cin >> l >> r;
		cout << pre[r] - pre[l-1] << endl;
	}
	
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

int n, m;

int num[100010];
int dif[100010];

int l, r, c;

int main() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; i ++) {
		cin >> num[i];
		dif[i] = num[i] - num[i-1];
		
	}
	
	while (m --) {
		cin >> l >> r >> c;
		dif[l] += c;
		dif[r + 1] -= c;
	}
	
	int ans = 0;
	
	for (int i = 1; i <= n; i ++) {
		ans += dif[i];
		cout << ans << " ";
	}
	
	return 0;
}
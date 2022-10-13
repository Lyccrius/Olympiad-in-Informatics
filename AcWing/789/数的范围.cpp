#include <bits/stdc++.h>

using namespace std;

int n, q;
int k;

int line[100010];

int l, r;
int mid;

int main() {
	cin >> n >> q;
	
	for (int i = 0; i < n; i ++) cin >> line[i];
	
	while (q --) {
		cin >> k;
		
		l = 0, r = n - 1;
		
		while (l < r) {
			mid = (l + r) / 2;
			if (line[mid] < k) l = mid + 1;
			else r = mid;
		}
		
		if (line[l] != k) {
			cout << "-1 -1" << endl;
			continue;
		}
		
		cout << l << " ";
		
		l = 0, r = n - 1;
		
		while (l < r) {
			mid = (l + r + 1) / 2;
			if (line[mid] > k) r = mid - 1;
			else l = mid;
		}
		
		cout << r << endl;
	}
	
	return 0;
}
#include <iostream>

int n, m;

int a[500010], t[500010];
int pre[500010];

using namespace std;

int lowbit(int x){
	return x & -x;
}

void change(int x, int k){
	while (x <= n){
		t[x] += k;
		x += lowbit(x);
	}

	return ;
}

int query(int x){
	int ans = 0;
	while (x > 0){
		ans += t[x];
		x -= lowbit(x);
	}

	return ans;
}

int main(){
	cin >> n >> m;

	for (int i = 1; i <= n; i ++){
		cin >> a[i];
		pre[i] = a[i] + pre[i-1];
		t[i] = pre[i] - pre[i-lowbit(i)];
	}

	int order;
	int x, y, k;

	for (int i = 1; i <= m; i ++){
		cin >> order;

		switch (order){
			case 1:
				cin >> x >> k;
				change(x, k);
				break;
			case 2:
				cin >> x >> y;
				cout << query(y) - query(x-1) << endl;
				break;
		}
	}

	return 0;
}
#include <bits/stdc++.h>

using namespace std;

struct node{
	int val;
	int l, r;
}tree[1000010];

int n, m;

int val[500010];
int add[500010];

int opt, x, y, k;

void build(int l, int r, int base) {
	int mid = (l + r) / 2;
	int lson = base * 2;
	int rson = base * 2 + 1;
	
	if (l == r) {
		tree[base].l = mid;
		tree[base].r = mid;
		tree[base].val = val[mid];
		add[mid] = base;
		return;
	}
	
	build(l, mid, lson);
	build(mid + 1, r, rson);
	
	tree[base].l = l;
	tree[base].r = r;
	tree[base].val = tree[lson].val + tree[rson].val;
	
	return;
}

void visit(int l, int r){
	
}

int main() {
	freopen("a.out", "w", stdout);
	
	cin >> n >> m;
	
	for (int i = 1; i <= n; i ++) cin >> val[i];
	
	build(1, n, 1);
	
	for (int i = 1; i <= m; i ++) {
		cin >> opt;
		switch(opt) {
			case 1: {
				cin >> x >> k;
				int a = add[x];
				while (a > 0) {
					tree[a].val += k;
					a /= 2;
				}
				break;
			}
			case 2:
				cin >> x >> y;
				cout << visit(x, y) << endl;
				break;
		}
	}
	
	cout << tree[1].val << endl;
	
	return 0;
}
#include <iostream>
#include <algorithm>

const int maxN = 1e6;
const int inf = 1e9;

int n, m;
int a[maxN + 10];
int b[maxN + 10];

struct SegmentTree {
	struct Node {
		int max;
		int min;
	} node[maxN * 4 + 10];

	void PushUp(int u) {
		node[u].max = std::max(node[u * 2].max, node[u * 2 + 1].max);
		node[u].min = std::min(node[u * 2].min, node[u * 2 + 1].min);
		return;
	}

	void Build(int u, int l, int r) {
		if (l == r) {
			node[u].max = b[l];
			node[u].min = b[l];
			return;
		}
		int mid = (l + r) / 2;
		Build(u * 2, l, mid);
		Build(u * 2 + 1, mid + 1, r);
		PushUp(u);
		return;
	}

	int QueryMax(int u, int l, int r, int s, int t) {
		if (s > t) return 0;
		if (s <= l && r <= t) {
			return node[u].max;
		}
		int mid = (l + r) / 2;
		if (t <= mid) return QueryMax(u * 2, l, mid, s, t);
		if (s >= mid + 1) return QueryMax(u * 2 + 1, mid + 1, r, s, t);
		return std::max(QueryMax(u * 2, l, mid, s, t), QueryMax(u * 2 + 1, mid + 1, r, s, t));
	}

	int QueryMin(int u, int l, int r, int s, int t) {
		if (s > t) return inf;
		if (s <= l && r <= t) {
			return node[u].min;
		}
		int mid = (l + r) / 2;
		if (t <= mid) return QueryMin(u * 2, l, mid, s, t);
		if (s >= mid + 1) return QueryMin(u * 2 + 1, mid + 1, r, s, t);
		return std::min(QueryMin(u * 2, l, mid, s, t), QueryMin(u * 2 + 1, mid + 1, r, s, t));
	}
} SGT;

bool check(int x) {
	//printf("checking dif = %d\n", x);
	for (int l = 1; l <= a[m + 1]; l++) {
		int r = l + x;
		int i = std::lower_bound(a + 1, a + n + 1, l) - a;
		int j = std::upper_bound(a + 1, a + n + 1, r) - a - 1;
		int need = (i - 1) + (n  - j);
		//printf("pos: [%d, %d], val: [%d, %d]\n", i, j, l, r);
		if (need > m) continue;
		if (1 != i) {
			int max1i = SGT.QueryMax(1, 1, n, 1, i - 1);
			int min1i = SGT.QueryMin(1, 1, n, 1, i - 1);
			//printf("[%d, %d]: min = %d, max = %d\n", 1, i - 1, min1i, max1i);
			if (max1i > r) continue;
			if (min1i < l) continue;
		}
		if (j != n) {	
			int maxjn = SGT.QueryMax(1, 1, n, j + 1, n);
			int minjn = SGT.QueryMin(1, 1, n, j + 1, n);
			//printf("[%d, %d]: min = %d, max = %d\n", j + 1, n, minjn, maxjn);
			if (maxjn > r) continue;
			if (minjn < l) continue;
		}
		/*
		int maxij = SGT.QueryMax(1, 1, n, i, j);
		int minij = SGT.QueryMin(1, 1, n, i, j);
		printf("[%d, %d]: min = %d, max = %d\n", i, j, minij, maxij);
		if (maxij > r) continue;
		if (minij < l) continue;
		*/
		return true;
		//printf("\n");
	}
	return false;
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) std::cin >> b[i];
	SGT.Build(1, 1, n);
	int l = 0;
	int r = inf;
	while (l < r) {
		int mid = (l + r) / 2;
		if (check(mid)) r = mid;
		else l = mid + 1;
		//printf("\n\n");
	}
	std::cout << l << '\n';
	return 0;
}
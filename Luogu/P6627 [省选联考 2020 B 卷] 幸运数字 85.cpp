#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1e5;

int n;
struct Node {
	int t;
	int L, R;
	int A, B;
	int w;
} node[maxN + 10];

vic raw;

int a[6 * maxN + 10];
int ans;

struct SegmentTree {
	struct Node {
		int val;
		int tag;
	} node[4 * 6 * maxN + 10];

	void MakeTag(int u, int w) {
		node[u].tag ^= w;
		return;
	}

	void PushUp(int u) {
		node[u].val = std::max(node[u * 2].val, node[u * 2 + 1].val);
		return;
	}

	void PushDown(int u) {
		if (!node[u].tag) return;
		MakeTag(u * 2, node[u].tag);
		MakeTag(u * 2 + 1, node[u].tag);
		node[u].tag = 0;
		return;
	}

	///*
	void Build(int u, int l, int r) {
		if (l == r) {
			node[u].val = raw[l];
			return;
		}
		int mid = (l + r) / 2;
		Build(u * 2, l, mid);
		Build(u * 2 + 1, mid + 1, r);
		return;
	}
	//*/

	//int a[6 * maxN + 10];

	/*
	void Build(int u, int l, int r) {
		//for (int i = l; i <= r; i++) a[i] = raw[i];
		return;
	}
	*/

	///*
	void Modify(int u, int l, int r, int s, int t, int w) {
		if (s > t) return;
		if (s <= l && r <= t) {
			MakeTag(u, w);
			return;
		}
		PushDown(u);
		int mid = (l + r) / 2;
		if (s <= mid) Modify(u * 2, l, mid, s, t, w);
		if (t >= mid + 1) Modify(u * 2 + 1, mid + 1, r, s, t, w);
		return;
	}
	//*/

	/*
	void Modify(int u, int l, int r, int s, int t, int w) {
		for (int i = s; i <= t; i++) a[i] ^= w;
		return;
	}
	*/

	///*
	void Query(int u, int l, int r) {
		if (l == r) {
			a[l] = node[u].val ^ node[u].tag;
			//printf("a[%d] = %d\n", l, a[l]);
			if (a[l] > a[ans]) ans = l;
			return;
		}
		PushDown(u);
		int mid = (l + r) / 2;
		//return std::max(Query(u * 2, l, mid), Query(u * 2 + 1, mid + 1, r));
		Query(u * 2, l, mid);
		Query(u * 2 + 1, mid + 1, r);
		return;
	}
	//*/

	/*
	int Query(int u, int l, int r) {
		int ret = 0;
		for (int i = l; i <= r; i++) ret = std::max(ret, a[i]);
		return ret;
	}
	*/
} SGT;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> node[i].t;
		if (node[i].t == 1) {
			std::cin >> node[i].L >> node[i].R >> node[i].w;
			raw.push_back(node[i].L - 1);
			raw.push_back(node[i].L);
			raw.push_back(node[i].L + 1);
			raw.push_back(node[i].R - 1);
			raw.push_back(node[i].R);
			raw.push_back(node[i].R + 1);
		} else if (node[i].t == 2) {
			std::cin >> node[i].A >> node[i].w;
			raw.push_back(node[i].A - 1);
			raw.push_back(node[i].A);
			raw.push_back(node[i].A + 1);
		} else if (node[i].t == 3) {
			std::cin >> node[i].B >> node[i].w;
			raw.push_back(node[i].B - 1);
			raw.push_back(node[i].B);
			raw.push_back(node[i].B + 1);
		}
	}
	std::sort(raw.begin(), raw.end());
	raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
	//for (int i = 0; i < raw.size(); i++) printf("%5d", i); printf("\n");
	//for (int i = 0; i < raw.size(); i++) printf("%5d", raw[i]); printf("\n");
	for (int i = 1; i <= n; i++) {
		if (node[i].t == 1) {
			node[i].L = std::lower_bound(raw.begin(), raw.end(), node[i].L) - raw.begin();
			node[i].R = std::lower_bound(raw.begin(), raw.end(), node[i].R) - raw.begin();
		} else if (node[i].t == 2) {
			node[i].A = std::lower_bound(raw.begin(), raw.end(), node[i].A) - raw.begin();
		} else if (node[i].t == 3) {
			node[i].B = std::lower_bound(raw.begin(), raw.end(), node[i].B) - raw.begin();
		}
	}
	//SGT.Build(1, 0, raw.size() - 1);
	for (int i = 1; i <= n; i++) {
		if (node[i].t == 1) {
			SGT.Modify(1, 0, raw.size() - 1, node[i].L, node[i].R, node[i].w);
			//printf("modify [%d, %d], %d\n", node[i].L, node[i].R, node[i].w);
		} else if (node[i].t == 2) {
			SGT.Modify(1, 0, raw.size() - 1, node[i].A, node[i].A, node[i].w);
			//printf("modify [%d, %d], %d\n", node[i].A, node[i].A, node[i].w);
		} else if (node[i].t == 3) {
			SGT.Modify(1, 0, raw.size() - 1, 0, node[i].B - 1, node[i].w);
			SGT.Modify(1, 0, raw.size() - 1, node[i].B + 1, raw.size() - 1, node[i].w);
			//printf("modify [%d, %d], %d\n", 0, node[i].B - 1, node[i].w);
			//printf("modify [%d, %d], %d\n", node[i].B + 1, raw.size() - 1, node[i].w);
		}
	}
	//std::cout << SGT.Query(1, 0, raw.size() - 1);
	SGT.Query(1, 0, raw.size() - 1);
	std::cout << a[ans] << ' ' << raw[ans] << '\n';
	return 0;
}
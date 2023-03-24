#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;

const int maxN = 2e5;

int k;
int n;
int a[maxN + 10];
int s[maxN + 10];
int t[maxN + 10];
vic raw;
int ans;

struct SegmentTree {
	struct Node {
		int val;
	} node[maxN + 10];

	void PushUp(int u) {
		node[u].val = std::max(node[u * 2].val, node[u * 2 + 1].val);
		return;
	}

	void Modify(int u, int l, int r, int pos, int val) {
		if (l == r) {
			node[u].val = std::max(node[u].val, val);
			//printf("modify [%d, %d] = %d\n", l, r, node[u].val);
			return;
		}
		int mid = (l + r) / 2;
		if (pos <= mid) Modify(u * 2, l, mid, pos, val);
		if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
		PushUp(u);
		return;
	}

	int Query(int u, int l, int r, int s, int t) {
		if (s <= l && r <= t) {
			//printf("Query [%d, %d], [%d, %d] = %d\n", l, r, s, t, node[u].val);
			return node[u].val;
		}
		int mid = (l + r) / 2;
		int ret = 0;
		if (t <= mid) ret = Query(u * 2, l, mid, s, t);
		else if (s >= mid + 1) ret = Query(u * 2 + 1, mid + 1, r, s, t);
		else ret = std::max(Query(u * 2, l, mid, s, t), Query(u * 2 + 1, mid + 1, r, s, t));
		//printf("Query [%d, %d], [%d, %d] = %d\n", l, r, s, t, ret);
		return ret;
	}

	void Clear() {
		for (int i = 1; i <= 4 * n; i++) node[i].val = 0;
		return;
	}
} SGT;

void mian() {
	std::cin >> n;
	std::fill(s + 1, s + n + 1, 1);
	std::fill(t + 1, t + n + 1, 1);
	ans = 1;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) raw.push_back(a[i]);
	std::sort(raw.begin(), raw.end());
	raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
	SGT.Clear();
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
	for (int i = 2; i <= n; i++) if (a[i] > a[i - 1]) t[i] += t[i - 1];
	for (int i = n; i >= 2; i--) if (a[i] > a[i - 1]) s[i - 1] += s[i];
	//for (int i = 1; i <= n; i++) printf("%d ", a[i]); printf("\n");
	//for (int i = 1; i <= n; i++) printf("%d ", t[i]); printf("\n");
	//for (int i = 1; i <= n; i++) printf("%d ", s[i]); printf("\n");
	for (int i = 1; i <= n; i++) ans = std::max(ans, t[i]);
	for (int i = 1; i <= n; i++) ans = std::max(ans, s[i]);
	for (int i = 1; i <= n; i++) {
		//printf("query [%d, %d] = %d\n", a[i] + 1, raw.size(), SGT.Query(1, 1, raw.size() + 1, a[i] + 1, raw.size() + 1));
		//printf("%d ", SGT.Query(1, 1, raw.size() + 1, a[i] + 1, raw.size() + 1));
		ans = std::max(ans, s[i] + SGT.Query(1, 1, raw.size() + 1, 1, a[i])), SGT.Modify(1, 1, raw.size() + 1, a[i - 1], t[i - 1]);
	}
	//printf("\n");
	std::cout << ans << '\n';
	return;
}

int main() {
    promote();
	std::cin >> k;
	while (k--) mian();
	return 0;
}
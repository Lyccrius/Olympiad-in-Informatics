#include <cstdio>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 5e5 + 10;

int n, m;
struct Range {
	int l, r;
	int L, R;
	int len;

	bool operator<(Range other) const {
		return len < other.len;
	}
} range[maxN];

int array[maxN << 1];
int cnt;
int tot;

void Discrete() {
	std::sort(array + 1, array + cnt + 1);
	tot = std::unique(array + 1, array + cnt + 1) - array - 1;
	return;
}

namespace SegmentTree {
	struct Node {
		int l, r;
		int lNode;
		int rNode;
		int value;
		int tag;
	};

	Node node[maxN << 3];
	int cnt;
	int root;

	void Build(int &xNode, int l, int r) {
		cnt++;
		xNode = cnt;
		node[xNode].l = l;
		node[xNode].r = r;
		if (l == r) return;
		int mid = (l + r) >> 1;
		Build(node[xNode].lNode, l, mid);
		Build(node[xNode].rNode, mid + 1, r);
		return;
	}

	void Clone(int &xNode) {
		cnt++;
		node[cnt] = node[xNode];
		xNode = cnt;
		return;
	}

	void PushDown(int xNode) {
		int lNode = node[xNode].lNode;
		int rNode = node[xNode].rNode;
		node[lNode].value += node[xNode].tag;
		node[rNode].value += node[xNode].tag;
		node[lNode].tag += node[xNode].tag;
		node[rNode].tag += node[xNode].tag;
		node[xNode].tag = 0;
		return;
	}

	void PushUp(int xNode) {
		node[xNode].value = std::max(node[node[xNode].lNode].value, node[node[xNode].rNode].value);
		return;
	}

	void Modify(int xNode, int l, int r, int value) {
		if (node[xNode].l >= l && node[xNode].r <= r) {
			node[xNode].value += value;
			node[xNode].tag += value;
			return;
		}
		if (node[xNode].tag) PushDown(xNode);
		int mid = (node[xNode].l + node[xNode].r) >> 1;
		if (l <= mid) Modify(node[xNode].lNode, l, r, value);
		if (r >= mid + 1) Modify(node[xNode].rNode, l, r, value);
		PushUp(xNode);
		return;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &range[i].l, &range[i].r);
		range[i].len = range[i].r - range[i].l;
		array[++cnt] = range[i].l;
		array[++cnt] = range[i].r;
	}
	std::sort(range + 1, range + n + 1);
	Discrete();
	SegmentTree::Build(SegmentTree::root, 1, tot);
	int ans = inf;
	int tail = 1;
	bool solved = false;
	for (int i = 1; i <= n; i++) {
		range[i].L = std::lower_bound(array + 1, array + tot + 1, range[i].l) - array;
		range[i].R = std::lower_bound(array + 1, array + tot + 1, range[i].r) - array;
		SegmentTree::Modify(1, range[i].L, range[i].R, 1);
		while (SegmentTree::node[SegmentTree::root].value >= m) {
			ans = std::min(ans, range[i].len - range[tail].len);
			SegmentTree::Modify(SegmentTree::root, range[tail].L, range[tail].R, -1);
			tail++;
			solved = true;
		}
	}
	if (solved) printf("%d\n", ans);
	else printf("-1\n");
	return 0;
}
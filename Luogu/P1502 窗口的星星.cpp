#include <cstdio>
#include <algorithm>

const int maxN = 1e4 + 10;

int T;
int n, W, H;
int x[maxN], y[maxN], l[maxN];

struct ScanLine {
	int x;
	int y1, y2;
	int delta;

	bool operator<(const ScanLine &other) const {
		if (x != other.x) return x < other.x;
		return delta < other.delta;
	}
} scanLine[maxN << 1];

int raw[maxN << 1];
int m;

struct SegmentTree {
	struct Node {
		int l, r;
		int lNode;
		int rNode;
		int dat;
		int tag;
	} node[maxN << 2];

	int cnt;
	int root;

	void Clone(int &xNode) {
		cnt++;
		node[cnt] = node[xNode];
		xNode = cnt;
		return;
	}

	void Build(int &xNode, int l, int r) {
		Clone(xNode);
		node[xNode].l = l;
		node[xNode].r = r;
		node[xNode].lNode = 0;
		node[xNode].rNode = 0;
		node[xNode].dat = 0;
		node[xNode].tag = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		Build(node[xNode].lNode, l, mid);
		Build(node[xNode].rNode, mid + 1, r);
		return;
	}

	void PushDown(int xNode) {
		if (node[xNode].tag) {
			node[node[xNode].lNode].dat += node[xNode].tag;
			node[node[xNode].lNode].tag += node[xNode].tag;
			node[node[xNode].rNode].dat += node[xNode].tag;
			node[node[xNode].rNode].tag += node[xNode].tag;
			node[xNode].tag = 0;
		}
		return;
	}

	void PushUp(int xNode) {
		node[xNode].dat = std::max(node[node[xNode].lNode].dat, node[node[xNode].rNode].dat);
		return;
	}

	void Modify(int &xNode, int l, int r, int val) {
		if (l <= node[xNode].l && node[xNode].r <= r) {
			node[xNode].dat += val;
			node[xNode].tag += val;
			return;
		}
		PushDown(xNode);
		if (l <= node[node[xNode].lNode].r) Modify(node[xNode].lNode, l, r, val);
		if (r >= node[node[xNode].rNode].l) Modify(node[xNode].rNode, l, r, val);
		PushUp(xNode);
		return;
	}
} SGT;

int ans;

void mian() {
	scanf("%d%d%d", &n, &W, &H);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &x[i], &y[i], &l[i]);
	for (int i = 1; i <= n; i++) {
		scanLine[i + n] = (ScanLine){x[i], y[i], y[i] + H - 1, l[i]};
		scanLine[i] = (ScanLine){W + x[i], y[i], y[i] + H - 1, -l[i]};
		raw[i + n] = y[i];
		raw[i] = H + y[i] - 1;
	}
	std::sort(raw + 1, raw + 2 * n + 1);
	m = std::unique(raw + 1, raw + 2 * n + 1) - raw - 1;
	for (int i = 1; i <= 2 * n; i++) {
		scanLine[i].y1 = std::lower_bound(raw + 1, raw + m + 1, scanLine[i].y1) - raw;
		scanLine[i].y2 = std::lower_bound(raw + 1, raw + m + 1, scanLine[i].y2) - raw;
	}
	std::sort(scanLine + 1, scanLine + 2 * n + 1);
	SGT.cnt = 0;
	SGT.root = 0;
	SGT.Build(SGT.root, 1, m);
	ans = 0;
	for (int i = 1; i <= 2 * n; i++) {
		SGT.Modify(SGT.root, scanLine[i].y1, scanLine[i].y2, scanLine[i].delta);
		ans = std::max(ans, SGT.node[SGT.root].dat);
	}
	printf("%d\n", ans);
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) mian();
	return 0;
}
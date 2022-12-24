#include <cstdio>
#include <algorithm>

const int maxN = 2e5 + 10;

int n;
int x1[maxN], y1[maxN], x2[maxN], y2[maxN];
int raw[maxN << 1];
int head;

struct Node {
	int x;
	int y1, y2;
	int k;

	bool operator<(const Node &other) const {
		return x < other.x;
	}
} scanLine[maxN];
int cnt;

struct SegmentTree {
	struct Node {
		int l, r;
		int lNode;
		int rNode;
		long long cnt;
		long long len;
	} node[maxN << 3];

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
		node[xNode].cnt = 0;
		node[xNode].len = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		Build(node[xNode].lNode, l, mid);
		Build(node[xNode].rNode, mid + 1, r);
		return;
	}

	void PushUp(int xNode) {
		if (xNode == 0) return;
		if (node[xNode].cnt) node[xNode].len = raw[node[xNode].r + 1] - raw[node[xNode].l];
		else node[xNode].len = node[node[xNode].lNode].len + node[node[xNode].rNode].len;
		return;
	}

	void Modify(int xNode, int l, int r, int val) {
		if (xNode == 0) return;
		if (l <= node[xNode].l && node[xNode].r <= r) {
			node[xNode].cnt += val;
			PushUp(xNode);
			return;
		}

		if (node[xNode].lNode && l <= node[node[xNode].lNode].r) Modify(node[xNode].lNode, l, r, val);
		if (node[xNode].rNode && r >= node[node[xNode].rNode].l) Modify(node[xNode].rNode, l, r, val);

		PushUp(xNode);
		return;
	}
} SGT;

void discrete() {
	head = 0;
	for (int i = 1; i <= n; i++) {
		raw[++head] = y1[i];
		raw[++head] = y2[i];
	}
	std::sort(raw + 1, raw + head + 1);
	head = std::unique(raw + 1, raw + head + 1) - raw - 1;
	for (int i = 1; i <= n; i++) {
		y1[i] = std::lower_bound(raw + 1, raw + head + 1, y1[i]) - raw;
		y2[i] = std::lower_bound(raw + 1, raw + head + 1, y2[i]) - raw;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
		if (x1[i] > x2[i]) std::swap(x1[i], x2[i]);
		if (y1[i] > y2[i]) std::swap(y1[i], y2[i]);
	}
	discrete();
	for (int i = 1; i <= n; i++) {
		scanLine[++cnt] = (Node){x1[i], y1[i], y2[i], 1};
		scanLine[++cnt] = (Node){x2[i], y1[i], y2[i], -1};
	}
	std::sort(scanLine + 1, scanLine + cnt + 1);
	SGT.Build(SGT.root, 1, head - 1);
	unsigned long long ans = 0;
	for (int i = 1; i < cnt; i++) {
		SGT.Modify(SGT.root, scanLine[i].y1, scanLine[i].y2 - 1, scanLine[i].k);
		ans += SGT.node[SGT.root].len * (scanLine[i + 1].x - scanLine[i].x);
	}
	printf("%llu\n", ans);
	return 0;
}
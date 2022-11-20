#include <cstdio>

const int maxn = 1e6 + 10;

int N, M;
int a[maxn];
int v, opt, loc, value;

struct SegmentTree {
	struct Node {
		int l;
		int r;
		int lNode;
		int rNode;
		int value;
	};

	Node node[maxn * 25];
	int cnt;
	int root[maxn * 25];

	void Build(int *array, int l, int r, int &xNode) {
		xNode = ++cnt;
		node[xNode].l = l;
		node[xNode].r = r;
		if (l == r) {
			node[xNode].value = array[l];
			return;
		}
		int mid = (l + r) >> 1;
		Build(array, l, mid, node[xNode].lNode);
		Build(array, mid + 1, r, node[xNode].rNode);
		return;
	}

	int Clone(int xNode) {
		cnt++;
		node[cnt] = node[xNode];
		return cnt;
	}

	void Modify(int &xNode, int loc, int value) {
		xNode = Clone(xNode);
		if (node[xNode].l == node[xNode].r) {
			node[xNode].value = value;
			return;
		}
		int mid = (node[xNode].l + node[xNode].r) >> 1;
		if (loc <= mid) Modify(node[xNode].lNode, loc, value);
		else Modify(node[xNode].rNode, loc, value);
		return;
	}
	
	int Query(int xNode, int loc) {
		if (node[xNode].l == node[xNode].r) return node[xNode].value;
		int mid = (node[xNode].l + node[xNode].r) >> 1;
		if (loc <= mid) return Query(node[xNode].lNode, loc);
		else return Query(node[xNode].rNode, loc);
	}
};

SegmentTree segmentTree;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) scanf("%d", &a[i]);
	segmentTree.Build(a, 1, N, segmentTree.root[0]);
	for (int i = 1; i <= M; i++) {
		scanf("%d%d", &v, &opt);
		segmentTree.root[i] = segmentTree.root[v];
		switch(opt) {
			case 1: {
				scanf("%d%d", &loc, &value);

				segmentTree.Modify(segmentTree.root[i], loc, value);
				break;
			}
			case 2: {
				scanf("%d", &loc);
				printf("%d\n", segmentTree.Query(segmentTree.root[i], loc));
				break;
			}
		}
	}
	return 0;
}
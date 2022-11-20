#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;
const int maxM = 2e5 + 10;

int n, m;

namespace PDS {
	struct Node {
		int l, r;
		int lNode;
		int rNode;
		int value;
		int depth;
	};

	int root[maxM];
	Node node[maxN * 30];
	int cnt;

	void Build(int &xNode, int l, int r) {
		cnt++;
		xNode = cnt;
		node[xNode].l = l;
		node[xNode].r = r;
		if (l == r) {
			node[xNode].value = l;
			node[xNode].depth = 1;
			return;
		}
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

	int Query(int xNode, int x) {
		if (node[xNode].l == node[xNode].r) return xNode;
		int mid = (node[xNode].l + node[xNode].r) >> 1;
		if (mid >= x) return Query(node[xNode].lNode, x);
		else return Query(node[xNode].rNode, x);
	}

	int Find(int version, int x) {
		int pos = Query(root[version], x);
		if (node[pos].value == x) return pos;
		return Find(version, node[pos].value);
	}

	int Modify(int xNode, int x, int value) {
		int oNode = xNode;
		Clone(xNode);
		if (node[xNode].l == node[xNode].r) {
			node[xNode].value = value;
			return xNode;
		}
		int mid = (node[xNode].l + node[xNode].r) >> 1;
		if (mid >= x) node[xNode].lNode = Modify(node[oNode].lNode, x, value);
		else node[xNode].rNode = Modify(node[oNode].rNode, x, value);
		return xNode;
	}
	
	int Add(int xNode, int x) {
		int oNode = xNode;
		Clone(xNode); 
		if (node[xNode].l == node[xNode].r) {
			node[xNode].depth++;
			return xNode;
		}
		int mid = (node[xNode].l + node[xNode].r) >> 1;
		if (mid >= x) node[xNode].lNode = Add(node[oNode].lNode, x);
		else node[xNode].rNode = Add(node[oNode].rNode, x);
		return xNode;
	}

	void Union(int version, int x, int y) {
		x = Find(version, x);
		y = Find(version, y);
		if (node[x].value != node[y].value) {
			if (node[x].depth > node[y].depth) std::swap(x, y);
			root[version] = Modify(root[version - 1], node[x].value, node[y].value);
			if (node[x].depth == node[y].depth) root[version] = Add(root[version], node[y].value);
		}
		return;
	}

	bool Check(int version, int x, int y) {
		x = Find(version, x);
		y = Find(version, y);
		if (node[x].value == node[y].value) return true;
		else return false;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	PDS::Build(PDS::root[0], 1, n);
	for (int i = 1; i <= m; i++) {
		int opt;
		int a, b;
		int k;
		scanf("%d", &opt);
		switch(opt) {
			case 1: {
				scanf("%d%d", &a, &b);
				PDS::root[i] = PDS::root[i - 1];
				PDS::Union(i, a, b);
				break;
			}
			case 2: {
				scanf("%d", &k);
				PDS::root[i] = PDS::root[k];
				break;
			}
			case 3: {
				scanf("%d%d", &a, &b);
				PDS::root[i] = PDS::root[i - 1];
				if (PDS::Check(i, a, b)) printf("1\n");
				else printf("0\n");
				break;
			}
		}
	}
	return 0;
}
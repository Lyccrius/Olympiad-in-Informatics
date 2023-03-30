#include <iostream>
#include <queue>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef unsigned int unt;
typedef unsigned long long ull;
//#define ull unt

const int maxN = 5e5;
const int logA = 32;

int n, k;
unt a[maxN + 10];
unt b[maxN + 10];
int h[maxN + 10];
ull ans;

struct Node {
	int from;
	int rank;
	unt val;

	bool operator<(const Node &other) const {
		if (val != other.val) return val < other.val;
		return from < other.from;
	}
};

std::priority_queue<Node> q;

struct TrieTree {
	struct Node {
		int son[2];
		int size;
	} node[maxN * logA + 10];

	int root;
	int ncnt;

	void Insert(unt val) {
		int u = root;
		//printf("Insert %d: \n", val);
		for (int p = logA - 1; p >= 0; p--) {
			int i = (val >> p) & 1;
			if (node[u].son[i] == 0) node[u].son[i] = ++ncnt;//, printf("ncnt = %d\n", ncnt);
			u = node[u].son[i];
			node[u].size++;
			//printf("%d, %d\n", i, u);
			//printf("%d", i);
		}
		//printf("%d\n", u);
		return;
	}

	unt Query(unt val, int rank) {
		unt ret = 0;
		int u = root;
		//printf("query %d, %d = \n", val, rank);
		for (int p = logA - 1; p >= 0; p--) {
			int i = (val >> p) & 1;
            //printf("%d: %d, %d(%d to %d)\n", i, rank, node[node[u].son[i^1]].size, u, node[u].son[i^1]);
			if (rank > node[node[u].son[i ^ 1]].size) {
				rank -= node[node[u].son[i ^ 1]].size;
				u = node[u].son[i];
                //if (!u) break;
				//printf("0");
			} else {
				ret |= (1ll << p);
				u = node[u].son[i ^ 1];
                //printf("1");
			}
            //if (!u) break;
		}
		//printf(" %d\n", ret);
		return ret;
	}
} TT;

int main() {
    TT.root = 1;
    TT.ncnt = 1;
	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) b[i] = b[i - 1] ^ a[i];
	for (int i = 0; i <= n; i++) TT.Insert(b[i]);
	for (int i = 0; i <= n; i++) q.push((Node) {i, 1, TT.Query(b[i], 1)});
	k *= 2;
	while (k--) {
		Node t = q.top();
		q.pop();
		ans += t.val;
		//printf("%d, %d, %d\n", t.from, t.rank, t.val);
		q.push((Node) {t.from, t.rank + 1, TT.Query(b[t.from], t.rank + 1)});
		//std::cout << ans << '\n';
	}
	ans /= 2;
	std::cout << ans << '\n';
	return 0;
}
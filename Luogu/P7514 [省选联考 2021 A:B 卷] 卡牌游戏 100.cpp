#include <iostream>
#include <algorithm>

const int maxN = 1e6;
const int inf = 1e9;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int ans = inf;

struct Node {
	int type;
	int pos;
	int val;

	bool operator<(const Node &other) const {
		return val < other.val;
	}
} node[maxN * 2 + 10];

int vis[maxN + 10];
int l = 1;
int r = 0;
int cntA = 0;
int tot = 0;

void Add(int x) {
	if (vis[node[x].pos] == 0) tot++;
	vis[node[x].pos] += node[x].type;
	if (node[x].type == 1) cntA++;
	return;
}

void Del(int x) {
	vis[node[x].pos] -= node[x].type;
	if (vis[node[x].pos] == 0) tot--;
	if (node[x].type == 1) cntA--;
	return;
}

bool check() {
	int cntB = tot - cntA;
	if (cntB > m) return false;
	if (tot < n) return false;
	return true;
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) std::cin >> b[i];
	for (int i = 1; i <= n; i++) node[i] = (Node) {1, i, a[i]};
	for (int i = 1; i <= n; i++) node[i + n] = (Node) {2, i, b[i]};
	std::sort(node + 1, node + 2 * n + 1);
	while (r <= 2 * n) {
		//printf("[%d, %d]\n", l, r);
		while (r <= 2 * n && !check()) Add(++r);
		if (r <= 2 * n && check()) ans = std::min(ans, node[r].val - node[l].val);
		//printf("ans = %d\n", ans);
		//while (l <= r && check()) 
		Del(l++);
	}
	std::cout << ans << '\n';
	return 0;
}
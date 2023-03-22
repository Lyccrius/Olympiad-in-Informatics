#include <iostream>
#include <algorithm>
#include <deque>
#include <cstring>

typedef std::deque<int> dic;

const int maxN = 3000;
const int maxM = 5000;
const int inf = 1e9 + 10;

int n, m;
int u, v;
int dis[maxN + 10][maxN + 10];
int vis[maxN + 10][maxN + 10];
int A, B, C, D;
int ans;

namespace graph {
	struct Node {
		int dis;
		int u;

		bool operator<(const Node &other) const {
			return dis > other.dis;
		}
	};

	typedef std::deque<Node> dnc;

	struct Vertex {
		int head;
		dnc i;
		dnc o;
	} vertex[maxN + 10];

	struct Edge {
		int head;
		int next;
	} edge[maxM + 10];

	int ecnt;

	void addEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	void BFS(int s) {
		dic q;
		for (int i = 1; i <= n; i++) dis[s][i] = inf;
		dis[s][s] = 0;
		q.push_back(s);
		while (q.size()) {
			int u = q.front();
			q.pop_front();
			if (vis[s][u]) continue;
			vis[s][u] = true;
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				if (dis[s][v] < inf) continue;
				dis[s][v] = dis[s][u] + 1;
				q.push_back(v);
			}
		}
		//for (int i = 1; i <= n; i++) printf("dis[%d][%d] = %d\n", s, i, dis[s][i]);
		return;
	}

	void mian() {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;
				if (dis[i][j] >= inf) continue;
				vertex[i].o.push_back((Node) {dis[i][j], j});
				vertex[j].i.push_back((Node) {dis[i][j], i});
			}
		}
		for (int i = 1; i <= n; i++) {
			std::sort(vertex[i].i.begin(), vertex[i].i.end());
			std::sort(vertex[i].o.begin(), vertex[i].o.end());
		}
		for (int b = 1; b <= n; b++) {
			//printf("b = %d, i %d, o %d\n", b, vertex[b].i.size(), vertex[b].o.size());
			for (int c = 1; c <= n; c++) {
				//printf("c = %d, i %d, o %d\n", c, vertex[c].i.size(), vertex[c].o.size());
				if (b == c) continue;
				for (int i = 0; i < std::min((int) vertex[b].i.size(), 3); i++) {
					for (int j = 0; j < std::min((int) vertex[c].o.size(), 3); j++) {
						int a = vertex[b].i[i].u;
						int d = vertex[c].o[j].u;
						//printf("%d %d %d %d\n", a, b, c, d);
						if (a == c) continue;
						if (b == d) continue;
						if (a == d) continue;
						if (dis[a][b] >= inf) continue;
						if (dis[b][c] >= inf) continue;
						if (dis[c][d] >= inf) continue;
						//printf("%d %d %d %d = %d\n", a, b, c, d, dis[a][b] + dis[b][c] + dis[c][d]);
						if (ans < dis[a][b] + dis[b][c] + dis[c][d]) {
							ans = dis[a][b] + dis[b][c] + dis[c][d];
							A = a;
							B = b;
							C = c;
							D = d;
						}
					}
				}
			}
		}
		std::cout << A << ' ' << B << ' ' << C << ' ' << D;
		return;
	}
}

int main() {
	std::cin >> n >> m;
	//std::fill(dis[0], dis[0] + (maxN + 10) * (maxN + 10), inf);
	//std::memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= m; i++) {
		std::cin >> u >> v;
		graph::addEdge(u, v);
	}
	for (int i = 1; i <= n; i++) graph::BFS(i);
	graph::mian();
	return 0;
}
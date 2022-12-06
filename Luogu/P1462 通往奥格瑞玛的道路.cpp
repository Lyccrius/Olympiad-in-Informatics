#include <cstdio>
#include <algorithm>
#include <queue>

const int maxN = 1e4 + 10;
const int maxM = 5e4 + 10;
const int inf = 1e9 + 10;

int N, M, B;
int a, b, c;

namespace Azeroth {
	struct Vertex {
		int head;
		int vis;
		int dis;
		int f;
	} city[maxN];
	struct Edge {
		int head;
		int next;
		int weight;
	} road[maxM << 1];
	int ecnt;

	void AddEdge(int tail, int head, int weight) {
		ecnt++;
		road[ecnt].head = head;
		road[ecnt].next = city[tail].head;
		road[ecnt].weight = weight;
		city[tail].head = ecnt;
		return;
	}

	int SPFA(int cost) {
		for (int i = 1; i <= N; i++) city[i].vis = false;
		for (int i = 1; i <= N; i++) city[i].dis = inf;
		city[1].dis = 0;
		std::queue<int> waiting;
		waiting.push(1);
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			city[u].vis = false;
			for (int e = city[u].head; e; e = road[e].next) {
				int v = road[e].head;
				int w = road[e].weight;
				if (city[v].dis > city[u].dis + w) {
					city[v].dis = city[u].dis + w;
					if (!city[v].vis && city[v].f <= cost) {
						city[v].vis = true;
						waiting.push(v);
					}
				}
			}
		}
		return city[N].dis;
	}
}

int main() {
	scanf("%d%d%d", &N, &M, &B);
	int maxF = 0;
	for (int i = 1; i <= N; i++) scanf("%d", &Azeroth::city[i].f), maxF = std::max(maxF, Azeroth::city[i].f);
	for (int i = 1; i <= M; i++) scanf("%d%d%d", &a, &b, &c), Azeroth::AddEdge(a, b, c), Azeroth::AddEdge(b, a, c);
	int l = std::max(Azeroth::city[1].f, Azeroth::city[N].f);
	int r = maxF;
	int ans;
	if (Azeroth::SPFA(inf) > B) {
		printf("AFK\n");
		return 0;
	}
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (Azeroth::SPFA(mid) <= B) r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
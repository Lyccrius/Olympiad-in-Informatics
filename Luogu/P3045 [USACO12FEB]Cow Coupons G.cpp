#include <cstdio>
#include <queue>

const int maxN = 5e4 + 10;
const long long maxM = 1e14 + 10;

int N, K; long long M;
int P[maxN], C[maxN];

struct Node {
	long long P;
	long long C;
	
	bool operator<(Node other) const {
		return C > other.C;
	}
};

struct N0de {
	long long P;
	long long C;

	bool operator<(N0de other) const {
		return P > other.P;
	}
};

struct N0d3 {
	long long P;
	long long C;

	bool operator<(N0d3 other) const {
		return P - C > other.P - other.C;
	}
};

std::priority_queue<Node> cow;
std::priority_queue<N0de> c0w;
std::priority_queue<N0d3> c03;
long long ans;

int main() {
	scanf("%d%d%lld", &N, &K, &M);
	for (int i = 1; i <= N; i++) scanf("%d%d", &P[i], &C[i]);
	for (int i = 1; i <= N; i++) cow.push((Node){P[i], C[i]});
	for (int i = 1; i <= K; i++) {
		if (!cow.empty() && M >= cow.top().C) {
			M -= cow.top().C;
			c03.push((N0d3){cow.top().P, cow.top().C});
			cow.pop();
			ans++;
		} else break;
	}
	while (!cow.empty()) c0w.push((N0de){cow.top().P, cow.top().C}), cow.pop();
	while (M && !c0w.empty()) {
		if (!c03.empty()) {
			int c0wP = c0w.top().P;
			int c0wC = c0w.top().C;
			int c03P = c03.top().P;
			int c03C = c03.top().C;
			int dif = c0wP - c0wC;
			int d1f = c03P - c03C;
			if (dif > d1f) {
				if (M + c03C - c03P - c0wC >= 0) {
					M = M + c03C - c03P;
					c0w.pop();
					c03.pop();
					c0w.push((N0de){c03P, c03C});
					c03.push((N0d3){c0wP, c0wC});
					continue;
				}
			}
		}
		if (M >= c0w.top().P) {
			M -= c0w.top().P;
			c03.push((N0d3){c0w.top().P, c0w.top().C});
			c0w.pop();
			ans++;
		} else break;
	}
	printf("%lld\n", ans);
	return 0;
}
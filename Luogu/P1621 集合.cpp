#include <cstdio>

const int maxP = 1e5 + 10;

int a, b, p;

struct DisJointSet {
	struct Node {
		int fa;
	};

	Node node[maxP];
	int cnt;

	void Init() {
		for (int i = a; i <= b; i++) node[i].fa = i;
		cnt = b - a + 1;
		return;
	}

	int Find(int x) {
		if (node[x].fa == x) return x;
		return node[x].fa = Find(node[x].fa);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);
		if (x == y) return;
		node[x].fa = y;
		cnt--;
		return;
	}
};

DisJointSet DJS;

bool isPrime(int x) {
	for (int i = 2; i * i <= x; i++) if (!(x % i)) return false;
	return true;
}

int next[maxP];
int first;

void PreWork() {
	int last = 0;
	for (int i = p; i <= b; i++) if (isPrime(i)) {
		if (last) next[last] = i;
		else first = i;
		last = i;
	}
	return;
}

int main() {
	scanf("%d%d%d", &a, &b, &p);
	DJS.Init();
	PreWork();
	for (int i = first; i; i = next[i]) {
		int last = 0;
		int j = 1;
		while (i * j < a) j++;
		while (i * j <= b) {
			if (last) {
				DJS.Union(last, i * j);
			}
			last = i * j;
			j++;
		}
	}
	printf("%d\n", DJS.cnt);
	return 0;
}
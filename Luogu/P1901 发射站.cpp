#include <cstdio>
#include <algorithm>
#include <stack>

const int maxN = 1e6 + 10;

int N;
int H[maxN];
int V[maxN];
int receive[maxN];
std::stack<int> preparation;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d%d", &H[i], &V[i]);
	for (int i = 1; i <= N; i++) {
		while (!preparation.empty() && H[preparation.top()] <= H[i]) receive[i] += V[preparation.top()], preparation.pop();
		if (!preparation.empty()) receive[preparation.top()] += V[i];
		preparation.push(i);
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) ans = std::max(ans, receive[i]);
	printf("%d\n", ans);
	return 0;
}
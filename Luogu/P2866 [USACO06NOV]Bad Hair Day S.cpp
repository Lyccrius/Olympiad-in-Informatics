#include <cstdio>
#include <stack>

const int maxN = 80000 + 10;

int N;
int h[maxN];
std::stack<int> cow;
long long ans;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &h[i]);
    for (int i = 1; i <= N; i++) {
		while (!cow.empty() && cow.top() <= h[i]) cow.pop();
		ans += cow.size();
		cow.push(h[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
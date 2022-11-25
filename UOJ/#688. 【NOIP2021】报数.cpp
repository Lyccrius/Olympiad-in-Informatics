#include <cstdio>

const int maxT = 2e5 + 10;
const int maxX = 1e7 + 10;

int T;
int x;
int num[maxX];
int ans[maxX];

bool Check(int a) {
	while (a) {
		if (a % 10 == 7) return true;
		a /= 10;
	}
	return false;
}

void Sign(int a) {
	for (int i = 1; i * a < maxX; i++) num[i * a] = true;
	return;
}

void Init() {
	int last = 0;
	for (int i = 1; i < maxX; i++) {
		if (num[i]) continue;
		if (Check(i)) {
			Sign(i);
			continue;
		}
		ans[last] = i;
		last = i;
	}
	return;
}

int main() {
	Init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &x);
		if (num[x]) printf("-1\n");
		else printf("%d\n", ans[x]);
	}
	return 0;
}
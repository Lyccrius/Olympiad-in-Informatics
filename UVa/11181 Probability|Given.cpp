#include <iostream>
#include <iomanip>

const int maxN = 20;

typedef double dbl;

int kase;
int n, r;
dbl p[maxN + 10];
int v[maxN + 10];
dbl s[maxN + 10];
dbl t;

void DFS(int now, int buy, dbl pro) {
	if (buy > r) return;
	//printf("DFS %d, %d, %lf\n", now, buy, pro);
	if (now > n)  {
		if (buy < r) return;
		for (int i = 1; i < now; i++) {
			if (v[i]) {
				s[i] += pro;
			}
		}
		t += pro;
		return;
	}
	v[now] = true;
	DFS(now + 1, buy + 1, pro * p[now]);
	v[now] = false;
	DFS(now + 1, buy, pro * (1 - p[now]));
	return;
}

void mian() {
	for (int i = 1; i <= n; i++) std::cin >> p[i];
	for (int i = 1; i <= n; i++) s[i] = 0; t = 0;
	DFS(1, 0, 1);
	std::cout << "Case " << ++kase << ":" << '\n';
	for (int i = 1; i <= n; i++) std::cout << std::setprecision(6) << s[i] / t << '\n';
	return;
}

int main() {
	std::cout << std::setiosflags(std::ios::fixed);
	while (std::cin >> n >> r && n && r) mian();
	return 0;
}
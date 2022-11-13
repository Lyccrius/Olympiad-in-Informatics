#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn = 10000 + 10;
const double pi = std::acos(-1.0);
const double eps = 1e-6;

int N, K;
double L[maxn];

bool check(double x) {
	int cnt = 0;
	for (int i = 1; i <= N; i++) cnt += std::floor(L[i] / x);
	if (cnt >= K) return true;
	return false;
}

int main() {
	scanf("%d%d", &N, &K);
	double maxL = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%lf", &L[i]);
		maxL = std::max(maxL, L[i]);
	}
	double l = 0;
	double r = maxL + eps;
	while (r - l > eps) {
		double m = (l + r) / 2;
		if (check(m)) l = m;
		else r = m;
	}
	printf("%.3lf\n", l);
	return 0;
}
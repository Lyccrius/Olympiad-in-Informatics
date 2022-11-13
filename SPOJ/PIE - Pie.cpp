#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn = 10000 + 10;
const double pi = std::acos(-1.0);
const double eps = 1e-6;

int T;
int N, F;
int r[maxn];

double S[maxn];

bool check(double x) {
	int cnt = 0;
	for (int i = 1; i <= N; i++) cnt += std::floor(S[i] / x);
	if (cnt >= F + 1) return true;
	return false;
}

int main() {
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		scanf("%d%d", &N, &F);
		double maxS = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &r[i]);
			S[i] = pi * r[i] * r[i];
			maxS = std::max(maxS, S[i]);
		}
		double L = 0;
		double R = maxS + eps;
		while (R - L > eps) {
			double M = (L + R) / 2;
			if (check(M)) L = M;
			else R = M;
		}
		printf("%.4lf\n", L);
	}
	return 0;
}
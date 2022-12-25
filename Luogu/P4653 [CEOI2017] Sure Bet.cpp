#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int n;
double A[maxN], B[maxN];

bool cmp(double a, double b) {
	return a > b;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &A[i], &B[i]);
	std::sort(A + 1, A + n + 1, cmp);
	std::sort(B + 1, B + n + 1, cmp);
	double sumA = 0;
	double sumB = 0;
	int i = 0;
	int j = 0;
	double ans = 0;
	while (i <= n && j <= n) {
		if (sumA < sumB) {
			ans = std::max(ans, sumA - i - j);
			sumA += A[++i];
		} else {
			ans = std::max(ans, sumB - i - j);
			sumB += B[++j];
		}
	}
	printf("%.4lf\n", ans);
	return 0;
}
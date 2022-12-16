#include <cstdio>

const int maxN = 1e5 + 10;
const double eps = 1e-6;
const long long inf = 1e10 + 10;

int n;
double p;
double a[200000], b[200000];

bool check(double x) {
	double q = p * x;
	double sum = 0;
	for (int i = 1; i <= n; i++) if (a[i] * x > b[i]) sum += (a[i] * x - b[i]);
	return sum <= q;
}

int main() {
	scanf("%d%lf", &n, &p);
	double sum = 0;
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &a[i], &b[i]), sum += a[i];
	if (sum <= p) {
		printf("%d\n", -1);
		return 0;
	}
	double l = 0;
	double r = inf;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.10lf\n", l);
	return 0;
}
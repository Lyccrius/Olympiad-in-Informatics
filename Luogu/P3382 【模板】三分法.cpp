#include <cstdio>

const int maxN = 13 + 10;
const double eps = 1e-7;

int N;
double l, r;
double a[maxN];

double f(double x) {
	double res = 0;
	for (int i = 0; i <= N; i++) res = res * x + a[i];
	return res;
}

int main() {
	scanf("%d%lf%lf", &N, &l, &r);
	for (int i = 0; i <= N; i++) scanf("%lf", &a[i]);
	while (r - l >= eps) {
		double gap = (r - l) / 3.0;
		double lMid = l + gap;
		double rMid = r - gap;
		if (f(lMid) < f(rMid)) l = lMid;
		else r = rMid;
	}
	printf("%.5lf\n", r);
	return 0;
}
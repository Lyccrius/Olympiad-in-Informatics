#include <cstdio>
#include <cmath>

long long n, x, p, q, t;
long long day = 1;
long long work;
long long next;
long long sleep;

int main() {
    scanf("%lld%lld%lld%lld", &n, &x, &p, &q);
	while (n--) {
		scanf("%lld", &t);
		if ((x - work - t + sleep) * q >= day * p * x && x - work > t) work += t;
		else {
			sleep += x - work;
			day++;
			next = std::ceil((q * (sleep + x - t) - p * day * x) * 1.0 / (x * p - x * q));
			if (next > 0) {
                sleep += x * next;
                day += next;
			}
		    work = t;
		}
	}
	printf("%lld\n", day);
    return 0;
}
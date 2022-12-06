#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int N, M;
long long A[maxN];

int Check(long long tot) {
	long long cnt = 1;
	long long sum = 0;
	for (int i = 1; i <= N; i++) {
		sum += A[i];
		if (sum > tot) {
			sum = A[i];
			cnt++;
		}
	}
	return cnt;
}

int main() {
	scanf("%d%d", &N, &M);
	long long maxA = 0;
	long long sumA = 0;
	for (int i = 1; i <= N; i++) scanf("%lld", &A[i]), maxA = std::max(maxA, A[i]), sumA += A[i];
	long long l = maxA;
	long long r = sumA;
	long long ans;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (Check(mid) <= M) r = mid - 1, ans = mid;
		else l = mid + 1, ans = l;
	}
	printf("%lld\n", ans);
	return 0;
}
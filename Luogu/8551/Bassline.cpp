#include <cstdio>
#include <algorithm>

const int maxn = 3e5 + 10;

int n;
int x, y;

int point[maxn];
int cover[maxn];
int last;
int cnt;
int pre = 1;
long long ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
    	point[x - 1] = 1;
        point[y] = 1;
    	cover[x]++;
        cover[y + 1]--;
    	last = std::max(last, y);
    }

	for (int i = 1; i <= last; i++) {
		cnt += cover[i];
		if (point[i]) {
            ans = std::max(ans, (long long)cnt * (i - pre));
            pre = i + 1;
        }
	}

	printf("%lld\n", ans);

    return 0;
}
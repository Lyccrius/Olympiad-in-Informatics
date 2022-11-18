#include <cstdio>
#include <algorithm>

const int inf = 0x3f3f3f3f;
const int mod = 1000000007;
const int maxN = 2e5 + 10;

int t;
int n;
int a[maxN];
int m;

struct Hero {
    int p, s;

    bool operator<(Hero other) const {
        return p < other.p;
    }

	bool operator<(int other) const {
		return p < other;
	}
} hero[maxN];


int main() {
    scanf("%d", &t);
    while (t--) {
        int maxA = 0, maxP = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            maxA = std::max(maxA, a[i]);
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &hero[i].p, &hero[i].s);
            maxP = std::max(maxP, hero[i].p);
        }
        if (maxA > maxP) {
            printf("-1\n");
            continue;
        }
        std::sort(hero + 1, hero + m + 1);
		for (int i = m - 1; i >= 1; i--) hero[i].s = std::max(hero[i].s, hero[i + 1].s);
        int date = 1;
        int killed = 0;
        int minS = inf;
        for (int i = 1; i <= n; ++i) {
            int fight = std::lower_bound(hero + 1, hero + m + 1, a[i]) - hero;
            minS = std::min(minS, hero[fight].s);
            if (minS + killed < i) {
                minS = hero[fight].s;
                date++;
                killed = i - 1;
            }
        }
       printf("%d\n", date);
    }
    return 0;
}
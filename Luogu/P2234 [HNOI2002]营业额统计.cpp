#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 32767 + 10;
const int inf = 1e9 + 10;

int n;

struct Node {
    int day;
	int val;

	bool operator<(Node other) const {
		return val < other.val;
	}
} a[maxN];

int ans;

int get(int x) {
    int l = inf;
	int r = inf;
    if (a[x].day == 1) return a[x].val;
    for (int i = x - 1; i >= 1; i--) if (a[i].day < a[x].day) {
        l = std::abs(a[i].val - a[x].val);
        break;
    }
    for (int i = x + 1; i <= n; i++) if (a[i].day < a[x].day) {
        r = std::abs(a[i].val - a[x].val);
        break;
    }
    return std::min(l, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i].val), a[i].day = i;
    std::sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) ans += get(i);
    printf("%d", ans);
    return 0;
}
#include <cstdio>
#include <algorithm>

const int inf = 1e9 + 10;

const int maxM = 500;
const int maxK = 500;

int m, k;
int p[maxM + 10];
int s[maxK + 10];
int t[maxK + 10];

bool check(int T) {
    int cur = m;
    for (int i = 1; i <= k; i++) s[i] = 0, t[i] = 0;
    for (int i = k; i >= 1; i--) {
        int t = 0;
        while (cur >= 1 && t + p[cur] <= T) t += p[cur], cur--;
    }
    return cur == 0;
}

int main() {
    scanf("%d%d", &m, &k);
    int sumP = 0;
    int minP = inf;
    for (int i = 1; i <= m; i++) scanf("%d", &p[i]), sumP += p[i], minP = std::min(minP, p[i]);
    int l = minP;
    int r = sumP;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    int cur = m;
    for (int i = k; i >= 1; i--) {
        int T = 0;
        while (cur >= 1 && T + p[cur] <= l) {
            T += p[cur];
            if (t[i] == 0) t[i] = cur;
            s[i] = cur;
            cur--;
        }
    }
    for (int i = 1; i <= k; i++) printf("%d %d\n", s[i], t[i]);
    return 0;
}
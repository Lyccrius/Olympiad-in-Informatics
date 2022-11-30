#include <cstdio>
#include <cstring>
#include <deque>

const int maxN = 5e5 + 10;
const long long inf = 1e9 + 10;

int n, d, k;
int x[maxN], s[maxN];

bool check(int g) {
    int l = std::max(1, d - g);
    int r = d + g;
    long long f[maxN];
    std::memset(f, -inf, sizeof(f));
    f[0] = 0;
    std::deque<int> house;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        while (x[cur] + l <= x[i]) {
            if (f[cur] != -inf) {
                while (!house.empty() && f[cur] >= f[house.back()]) house.pop_back();
                house.push_back(cur);
            }
            cur++;
        }
        while (!house.empty() && x[house.front()] + r < x[i]) house.pop_front();
        if (!house.empty()) f[i] = f[house.front()] + s[i];
        if (f[i] >= k) return true;
    }
    return false;
}

int main() {
    scanf("%d%d%d", &n, &d, &k);
    for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &s[i]);
    int l = 1;
    int r = x[n] - d;
    int ans = -1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid, ans = mid;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
#include <cstdio>
#include <algorithm>
#include <deque>

const int maxn = 5e5 + 10;

int n, m;
int p[maxn];

int S[maxn];
std::deque<int> q;
int ans;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        S[i] = S[i - 1] + p[i];
        if (i == 1) ans = S[i];
        while (!q.empty() && i - q.front() > m) q.pop_front();
        if (!q.empty()) ans = std::max(ans, S[i] - S[q.front()]);
        while (!q.empty() && S[q.back()] >= S[i]) q.pop_back();
        q.push_back(i);
    }
    printf("%d\n", ans);
    return 0;
}
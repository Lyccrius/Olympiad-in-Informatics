#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const lxl maxN = 40;
const lxl maxM = 1e18;

lxl N, M;
lxl a[maxN + 10];
lxl ans;

std::vector<lxl> v[2];

void DFS(int now, int st, int ed, int type, lxl sum) {
    if (sum > M) return;
    if (now > ed) {
        v[type].push_back(sum);
        return;
    }
    DFS(now + 1, st, ed, type, sum);
    DFS(now + 1, st, ed, type, sum + a[now]);
    return;
}

int main() {
    promote();
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    std::sort(a + 1, a + N + 1);
    lxl mid = N >> 1;
    DFS(1, 1, mid, 0, 0);
    DFS(mid + 1, mid + 1, N, 1, 0);
    std::sort(v[0].begin(), v[0].end());
    std::sort(v[1].begin(), v[1].end());
    lxl i = 0;
    lxl j = v[1].size() - 1;
    while (i < v[0].size()) {
        while (v[0][i] + v[1][j] > M) j--;
        ans += j + 1;
        i++;
    }
    std::cout << ans << '\n';
    return 0;
}
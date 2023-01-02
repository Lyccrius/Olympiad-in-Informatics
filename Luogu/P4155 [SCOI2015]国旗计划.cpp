#include <cstdio>
#include <algorithm>

const int maxN = 2e5;
const int logN = 17;

long long N, M;
long long C[maxN + 10], D[maxN + 10];

struct Node {
    long long id;
    long long l, r;

    bool operator<(const Node &other) const {
        return l < other.l;
    }
} soldier[maxN * 2 + 10];

int st[maxN * 2 + 10][logN + 1 + 10];
int ans[maxN + 10];

int main() {
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%lld%lld", &C[i], &D[i]);
        if (C[i] > D[i]) D[i] += M;
        soldier[i].id = i;
        soldier[i].l = C[i];
        soldier[i].r = D[i];
    }
    std::sort(soldier + 1, soldier + N + 1);
    for (int i = 1; i <= N; i++) {
        soldier[N + i].l = soldier[i].l + M;
        soldier[N + i].r = soldier[i].r + M;
    }
    int head = 0;
    for (int i = 1; i <= N * 2; i++) {
        while (head < N * 2 && soldier[head + 1].l <= soldier[i].r) head++;
        st[i][0] = head;
    }
    for (int p = 1; p <= logN + 1; p++) for (int i = 1; i <= N * 2; i++) st[i][p] = st[st[i][p - 1]][p - 1];
    for (int i = 1; i <= N; i++) {
        int res = 2;
        int now = i;
        for (int p = logN + 1; p >= 0; p--) if (st[now][p] && soldier[st[now][p]].r < soldier[i].l + M) res += (1 << p), now = st[now][p];
        ans[soldier[i].id] = res;
    }
    for (int i = 1; i <= N; i++) printf("%d ", ans[i]);
    return 0;
}
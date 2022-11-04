#include <cstdio>
#include <cmath>
#include <algorithm>

const long long inf = 1e18 + 10;
const int maxn = 1e5 + 10;
const int maxt = 30;

struct ST {
    struct node{
        long long num[5];
    };

    node table[maxn][maxt];
    int time[maxn];

    node Max (node x, node y) {
        return (node) {
            std::max(x.num[0], y.num[0]),
            std::max(x.num[1], y.num[1]),
            std::min(x.num[2], y.num[2]),
            std::min(x.num[3], y.num[3])
        };
    }

    void Prework (int *array, int n) {
        time[0] = 0;
        time[1] = 0;
        for (int i = 2; i <= n; i++) time[i] = time[i >> 1] + 1;
        for (int i = 1; i <= n; i++) {
            if (array[i] >= 0) {
                table[i][0] = (node) {array[i], -inf, array[i], inf};
            } else {
                table[i][0] = (node) {-inf, array[i], inf, array[i]};
            }
        }
        for (int j = 1; j <= time[n]; j++) {
            for (int i = 1; i + (1 << j) <= n + 1; i++) {
                table[i][j] = Max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
        return;
    }

    node Query (int l, int r) {
        int t = time[r - l + 1];
        return Max(table[l][t], table[r - (1 << t) + 1][t]);
    }
};

bool check(long long x) {
    return (x > -inf && x < inf);
}

int n, m, q;
int A[maxn], B[maxn];
int l1, r1, l2, r2;

ST L, Q;

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &B[i]);

    L.Prework(A, n);
    Q.Prework(B, m);

    while (q--) {
        scanf("%d%d", &l1, &r1);
        scanf("%d%d", &l2, &r2);
        ST::node ansL = L.Query(l1, r1);
        ST::node ansQ = Q.Query(l2, r2);
        long long ans = -inf;
        for (int i = 0; i < 4; i++) {
            if (check(ansL.num[i])) {
                long long res = inf;
                for (int j = 0; j < 4; j++) {
                    if (check(ansQ.num[j])) {
                        res = std::min(res, (long long)ansL.num[i] * ansQ.num[j]);
                    }
                }
                ans =std::max(ans, res);
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}
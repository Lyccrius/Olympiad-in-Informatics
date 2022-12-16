#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;

int N, T;

struct Heap {
    int m, v;
    double w;

    bool operator<(Heap other) const {
        return w > other.w;
    }
} coin[maxN];

double res = 0;

int main() {
    scanf("%d%d", &N, &T);
    for (int i = 1; i <= N; i++) scanf("%d%d", &coin[i].m, &coin[i].v), coin[i].w = (double)coin[i].v / coin[i].m;
    std::sort(coin + 1, coin + N + 1);
    for (int i = 1; i <= N && T; i++) {
        while (T && coin[i].m) {
            res += coin[i].w;
            coin[i].m--;
            T--;
        }
    }
    printf("%.2lf\n", res);
    return 0;
}
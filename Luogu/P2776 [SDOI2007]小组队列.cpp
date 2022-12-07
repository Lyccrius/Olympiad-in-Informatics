#include <cstdio>
#include <queue>

const int maxt = 1000 + 10;
const int maxn = 100000 + 10;

int n, m;
int T;
int bel[maxn];
char opt[10];

int main() {
    std::queue<int> Q[maxn];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        bel[i] = num;
    }
    scanf("%d", &T);
    while (T--) {
        scanf(" %s", opt);
        if (opt[1] == 'u') {
            int X, Y;
            scanf("%d", &X);
            Y = bel[X];
            if (Q[Y].empty()) Q[maxn - 1].push(Y);
            Q[Y].push(X);
        } else {
            int X, Y;
            Y = Q[maxn - 1].front();
            X = Q[Y].front();
            printf("%d\n", X);
            Q[Y].pop();
            if (Q[Y].empty()) Q[maxn - 1].pop();
        }
    }
    printf("\n");
    return 0;
}
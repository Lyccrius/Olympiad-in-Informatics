#include <cstdio>
#include <queue>

const int maxt = 1000 + 10;
const int maxn = 1000 + 10;

int k;
int t;
int n;
int bel[maxt * maxn];
char opt[10];

int main() {
    while (scanf("%d", &t) == 1 && t) {
        k++;
        printf("Scenario #%d\n", k);
        std::queue<int> Q[maxn];
        for (int i = 1; i <= t; i++) {
            scanf("%d", &n);
            for (int j = 1; j <= n; j++) {
                int num;
                scanf("%d", &num);
                bel[num] = i;
            }
        }
        while (scanf("%s", opt) && opt[0] != 'S') {
            if (opt[0] == 'E') {
                int X, Y;
                scanf("%d", &X);
                Y = bel[X];
                if (Q[Y].empty()) Q[0].push(Y);
                Q[Y].push(X);
            } else {
                int X, Y;
                Y = Q[0].front();
                X = Q[Y].front();
                printf("%d\n", X);
                Q[Y].pop();
                if (Q[Y].empty()) Q[0].pop();
            }
        }
        printf("\n");
    }
    return 0;
}
#include <cstdio>
#include <algorithm>

const int maxn = 10000 + 10;

int t;

int N;
int L, T, n;

struct Ant {
    int id;
    int order;
    int turn;
    int x;
};

Ant ant[maxn];
Ant antT[maxn];

bool cmpByX(Ant a, Ant b) {
    return a.x < b.x;
}

bool cmpById(Ant a, Ant b) {
    return a.id < b.id;
}

int main() {
    scanf("%d", &N);
    for (int t = 1; t <= N; t++) {
        scanf("%d%d%d", &L, &T, &n);
        int x;
        char c;
        for (int i = 1; i <= n; i++) {
            scanf("%d %c", &x, &c);
            ant[i].id = i;
            ant[i].turn = (c == 'L') ? -1 : 1;
            ant[i].x = x;
            antT[i].turn = ant[i].turn;
            antT[i].x = x + ant[i].turn * T;
        }
        std::sort(ant + 1, ant + n + 1, cmpByX);
        for (int i = 1; i <= n; i++) {
            ant[i].order = i;
        }
        std::sort(antT + 1, antT + n + 1, cmpByX);
        for (int i = 1; i < n; i++) {
            if (antT[i].x == antT[i + 1].x) {
                antT[i].turn = 0;
                antT[i + 1].turn = 0;
            }
        }
        std::sort(ant + 1, ant + n + 1, cmpById);
        printf("Case #%d:\n", t);
        for (int i = 1; i <= n; i++) {
            if (antT[ant[i].order].x < 0 || antT[ant[i].order].x > L) {
                printf("Fell off\n");
                continue;
            }
            printf("%d ", antT[ant[i].order].x);
            switch(antT[ant[i].order].turn) {
                case -1: {
                    printf("L\n");
                    break;
                }
                case 0: {
                    printf("Turning\n");
                    break;
                }
                case 1: {
                    printf("R\n");
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}
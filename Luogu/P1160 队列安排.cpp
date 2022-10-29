#include <bits/stdc++.h>

const int maxn = 1e5 + 10;

struct ClassMate{
    int left;
    int right;
}mates[maxn];

int N;
int k, p;
int M;
int x;

int main() {
    mates[0].left = 0;
    mates[0].right = 1;
    mates[1].left = 0;
    mates[1].right = 0;

    scanf("%d", &N);

    for (int i = 2; i <= N; i++) {
        scanf("%d%d", &k, &p);

        if (p) {
            mates[i].left = k;
            mates[i].right = mates[k].right;
            mates[k].right = i;
            mates[mates[i].right].left = i;
        } else {
            mates[i].right = k;
            mates[i].left = mates[k].left;
            mates[k].left = i;
            mates[mates[i].left].right = i;
        }
    }

    scanf("%d", &M);

    while (M--) {
        scanf("%d", &x);

        if (mates[x].left || mates[x].right) {
            mates[mates[x].left].right = mates[x].right;
            mates[mates[x].right].left = mates[x].left;

            mates[x].left = 0;
            mates[x].right = 0;
        }
    }

    int last = 0;

    while (mates[last].right) {
        if (last) {
            printf(" ");
        }

        printf("%d", mates[last].right);

        last = mates[last].right;
    }

    printf("\n");

    return 0;
}
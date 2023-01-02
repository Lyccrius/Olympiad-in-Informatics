#include <cstdio>

const int maxN = 1.5e5;
const int sqrtN = 387;

int n, m;
int value[maxN + 10];
int block[maxN + 10][sqrtN + 10];

void PreWork() {
    for (int i = 1; i <= n; i++) {
        for (int x = 1; x <= sqrtN; x++) {
            int y = i % x;
            block[x][y] += value[i];
        }
    }
    return;
}

int Query(int x, int y) {
    if (x <= sqrtN) return block[x][y];
    int ret = 0;
    for (int i = y; i <= n; i += x) ret += value[i];
    return ret;
}

void Modify(int x, int y) {
    for (int i = 1; i <= sqrtN; i++) {
        block[i][x % i] += y - value[x];
    }
    value[x] = y;
    return;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &value[i]);
    PreWork();
    while (m--) {
        char cmd;
        int x, y;
        scanf(" %c%d%d", &cmd, &x, &y);
        if (cmd == 'A') printf("%d\n", Query(x, y));
        else Modify(x, y);
    }
    return 0;
}
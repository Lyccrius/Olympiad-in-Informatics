#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 300;
const int maxM = 300;
const int maxQ = 2e5;
const int maxC = 100;

int n, m;
int a[maxN + 10][maxM + 10];
int Q;
int op;
int x, y, c;
int x1, x2, y1, y2;

int lowbit(int val) {
    return val & -val;
}

struct BinaryIndexedTree {
    struct BinaryIndexedTree2 {
        int node[maxM + 10][maxC + 10];

        void Add(int y, int c, int val) {
            while (y <= m) {
                node[y][c] += val;
                y += lowbit(y);
            }
            return;
        }

        int Ask(int y, int c) {
            int ret = 0;
            while (y >= 1) {
                ret += node[y][c];
                y -= lowbit(y);
            }
            return ret;
        }
    } BIT[maxN + 10];

    void Add(int x, int y, int c, int val) {
        while (x <= n) {
            BIT[x].Add(y, c, val);
            x += lowbit(x);
        }
        return;
    }

    int Ask(int x, int y, int c) {
        //printf("Ask(%d, %d, %d)\n", x, y, c);
        int ret = 0;
        while (x >= 1) {
            ret += BIT[x].Ask(y, c);
            //printf("%d, %d\n", x, ret);
            x -= lowbit(x);
        }
        return ret;
    }
} BIT;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j], BIT.Add(i, j, a[i][j], 1);
    /*
    for (int c = 1; c <= 3; c++) {
        printf("\n");
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) printf("%d ", BIT.BIT[i].node[j][c]);
            printf("\n");
        }
        printf("\n");
    }
    */
    std::cin >> Q;
    for (int i = 1; i <= Q; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> x >> y >> c;
            BIT.Add(x, y, a[x][y], -1);
            BIT.Add(x, y, c, 1);
            a[x][y] = c;
        } else {
            std::cin >> x1 >> x2 >> y1 >> y2 >> c;
            //printf("%d %d %d %d\n", BIT.Ask(x2, y2, c), BIT.Ask(x1 - 1, y2, c), BIT.Ask(x2, y1 - 1, c), BIT.Ask(x1 - 1, y1 - 1, c));
            std::cout << BIT.Ask(x2, y2, c) - BIT.Ask(x1 - 1, y2, c) - BIT.Ask(x2, y1 - 1, c) + BIT.Ask(x1 - 1, y1 - 1, c) << '\n';
        }
    }
    return 0;
}
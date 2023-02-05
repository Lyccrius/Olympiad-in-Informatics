#include <iostream>
#include <cstdio>

const int maxN = 1e5;
const int maxM = 1e5;

int T;
int N, M;
char op;
int a, b;

struct DisjointSetUnion {
    int node[maxN + 10];

    void Init() {
        for (int i = 1; i <= N * 2; i++) {
            node[i] = i;
        }
        return;
    }

    int Find(int x) {
        if (node[x] == x) return x;
        return node[x] = Find(node[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        node[x] = y;
        return;
    }
} DSU;

void mian() {
    //std::cin >> N >> M;
    scanf("%d%d", &N, &M);
    DSU.Init();
    for (int i = 1; i <= M; i++) {
        //std::cin >> op >> a >> b;
        scanf(" %c%d%d", &op, &a, &b);
        if (op == 'D') {
            DSU.Union(a + N, b);
            DSU.Union(a, b + N);
        } else {
            if (N == 2) {
                //std::cout << "In the same gang.\n";
                printf("In the same gang.\n");
                continue;
            }
            if (DSU.Find(a) == DSU.Find(b) || DSU.Find(a + N) == DSU.Find(b + N)) {
                //std::cout << "In the same gang.\n";
                printf("In the same gang.\n");
                continue;
            }
            if (DSU.Find(a) == DSU.Find(b + N) || DSU.Find(a + N) == DSU.Find(b)) {
                //std::cout << "In different gangs.\n";
                printf("In different gangs.\n");
                continue;
            }
            //std::cout << "Not sure yet.\n";
            printf("Not sure yet.\n");
        }
    }
    return;
}

int main() {
    //std::cin >> T;
    scanf("%d", &T);
    while (T--) mian();
    return 0;
}
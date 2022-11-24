#include <cstdio>


const int maxN = 5e4 + 10;

int N, K;
int type, X, Y;

namespace Chain {
    struct Node {
        int fa;
    } node[maxN * 3];

    void Init() {
        for (int i = 1; i <= N * 3; i++) node[i].fa = i;
        return;
    }

    int Find(int x) {
        if (node[x].fa == x) return x;
        return node[x].fa = Find(node[x].fa);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        node[x].fa = y;
        return;
    }
}

int main() {
    scanf("%d%d", &N, &K);
    int lie = 0;
    Chain::Init();
    for (int i = 1; i <= K; i++) {
        scanf("%d%d%d", &type, &X, &Y);
        if (X > N || Y > N) {
            lie++;
            continue;
        }
        switch (type) {
            case 1: {
                if (Chain::Find(X) == Chain::Find(Y + N) || Chain::Find(Y) == Chain::Find(X + N)) lie++;
                else {
                    Chain::Union(X, Y);
                    Chain::Union(X + N, Y + N);
                    Chain::Union(X + N + N, Y + N + N);
                }
                break;
            }
            case 2: {
                if (Chain::Find(X) == Chain::Find(Y) || Chain::Find(Y) == Chain::Find(X + N)) lie++;
                else {
                    Chain::Union(X, Y + N);
                    Chain::Union(X + N, Y + N + N);
                    Chain::Union(X + N + N, Y);
                }
                break;
            }
        }
    }
    printf("%d\n", lie);
    return 0;
}
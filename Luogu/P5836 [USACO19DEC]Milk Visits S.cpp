#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int N, M;
char S[maxN + 10];
int X, Y;
int A, B;
char C;

struct DisjointSetUnion {
    int fa[maxN + 10];

    int Find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = Find(fa[x]);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        fa[x] = y;
        return;
    }
} DSU;

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> S[i];
    for (int i = 1; i <= N; i++) DSU.fa[i] = i;
    for (int i = 1; i < N; i++) {
        std::cin >> X >> Y;
        if (S[X] == S[Y]) DSU.Union(X, Y);
    }
    for (int i = 1; i <= M; i++) {
        std::cin >> A >> B;
        std::cin >> C;
        if (DSU.Find(A) == DSU.Find(B) && S[A] != C) std::cout << 0;
        else std::cout << 1;
    }
    return 0;
}
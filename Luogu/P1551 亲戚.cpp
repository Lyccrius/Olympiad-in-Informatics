#include <cstdio>

const int maxN = 5000 + 10;

int n, m, p;

namespace Relation {
    int relations[maxN];

    void Init() {
        for (int i = 1; i <= n; i++) relations[i] = i;
        return;
    }

    int Query(int x) {
        if (relations[x] == x) return x;
        return relations[x] = Query(relations[x]);
    }

    void Merge(int x, int y) {
        x = Query(x);
        y = Query(y);
        relations[x] = y;
        return;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &p);
    Relation::Init();
    for (int i = 1; i <= m; i++) {
        int Mi, Mj;
        scanf("%d%d", &Mi, &Mj);
        Relation::Merge(Mi, Mj);
    }
    for (int i = 1; i <= p; i++) {
        int Pi, Pj;
        scanf("%d%d", &Pi, &Pj);
        Pi = Relation::Query(Pi);
        Pj = Relation::Query(Pj);
        if (Pi == Pj) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
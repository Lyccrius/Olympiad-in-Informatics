#include <cstdio>
#include <cmath>

const int maxN = 30000 + 10;

int T;

namespace Galaxy {
    struct Node {
        int row;
        int rank;
    };

    Node warship[maxN];
    int size[maxN];

    void Init() {
        for (int i = 1; i <= 30000; i++) {
            warship[i].row = i;
            warship[i].rank = 0;
            size[i] = 1;
        }
        return;
    }

    int  Query(int x) {
        if (x == warship[x].row) return x;
        int row = Query(warship[x].row);
        warship[x].rank += warship[warship[x].row].rank;
        return warship[x].row = row;
    }

    void Merge(int x, int y) {
        x = Query(x);
        y = Query(y);
        warship[x].row = y;
        warship[x].rank = size[y];
        size[y] += size[x];
        return;
    }
}

int main() {
    scanf("%d", &T);
    Galaxy::Init();
    for (int kase = 1; kase <= T; kase++) {
        char opt;
        int i, j;
        scanf(" %c%d%d", &opt, &i, &j);
        if (opt == 'M') Galaxy::Merge(i, j);
        else {
            if (Galaxy::Query(i) == Galaxy::Query(j)) printf("%d\n", std::abs(Galaxy::warship[i].rank - Galaxy::warship[j].rank) - 1);
            else printf("-1\n");
        }
    }
    return 0;
}
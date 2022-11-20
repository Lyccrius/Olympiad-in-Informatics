#include <cstdio>
#include <vector>

const int maxN = 1000 + 10;
const int maxM = 5000 + 10;

int n;
int m;

namespace Group {
    struct Node {
        int group;
    };

    Node person[maxN];

    int Query(int x) {
        if (x == person[x].group) return x;
        return person[x].group = Query(person[x].group);
    }

    void Merge(int x, int y) {
        x = Query(x);
        y = Query(y);
        person[x].group = y;
        return;
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d", &m);
    std::vector<int> enemy[maxN];
    for (int i = 1; i <= n; i++) Group::person[i].group = i;
    for (int i = 1; i <= m; i++) {
        char opt;
        int p, q;
        scanf(" %c%d%d", &opt, &p, &q);
        if (opt == 'F') Group::Merge(p, q);
        else enemy[p].push_back(q), enemy[q].push_back(p);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < enemy[i].size(); j++) {
            for (int k = j + 1; k < enemy[i].size(); k++) {
                Group::Merge(enemy[i][j], enemy[i][k]);
            }
        }
    }
    bool visited[maxN];
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int group = Group::Query(i);
        if (visited[group]) continue;
        visited[group] = true;
        cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}
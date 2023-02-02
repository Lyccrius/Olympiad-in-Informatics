#include <iostream>
#include <string>
#include <map>

const int maxN = 5e5;

std::string str1, str2;
std::map<std::string, int> list;
int tot;
int cnt;
int deg[maxN + 10];
bool ok = true;

struct DisjointSetUnion {
    int node[maxN + 10];

    void Init() {
        for (int i = 1; i <= maxN; i++) node[i] = i;
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

int main() {
    DSU.Init();
    while (std::cin >> str1 >> str2) {
        if (!list[str1]) list[str1] = ++tot;
        if (!list[str2]) list[str2] = ++tot;
        deg[list[str1]]++;
        deg[list[str2]]++;
        int f1 = DSU.Find(list[str1]);
        int f2 = DSU.Find(list[str2]);
        if (f1 == f2) continue;
        DSU.Union(f1, f2);
        cnt++;
    }
    if (cnt < tot - 1) ok = false;
    cnt = 0;
    for (int i = 1; i <= tot; i++) if (deg[i] & 1) cnt++;
    if (cnt > 2) ok = false;
    if (ok) std::cout << "Possible";
    else std::cout << "Impossible";
    return 0;
}
#include <iostream>
#include <string>
#include <vector>

typedef long long lxl;
typedef std::string str;

const int maxN = 3e5;
const int maxM = 5e5;

const str _Add = "Add";
const str _Delete = "Delete";
const str _Return = "Return";

int n, m;

struct Option {
    str opt;
    int a, b;
    int k;
} option[maxM + 10];

struct Result {
    lxl sum;
    int cnt;
    int bak;
};

std::vector<Result> res;

struct DisjointSetUnion {
    struct Node {
        int fa;
        int size;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        for (int i = 1; i <= n; i++) node[i].size = 1;
        res.push_back((Result) {0, 0, 0});
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return Find(node[u].fa);
    }

    void Union(int u, int v, int w) {
        u = Find(u);
        v = Find(v);
        res.push_back(res.back());
        res.back().bak = 0;
        if (u == v) return;
        if (node[u].size > node[v].size) std::swap(u, v);
        res.back().sum += w;
        res.back().cnt++;
        res.back().bak = u;
        node[u].fa = v;
        node[v].size += node[u].size;
        return;
    }

    void Delete(int k) {
        while (k--) {
            int u = res.back().bak;
            res.pop_back();
            node[node[u].fa].size -= node[u].size;
            node[u].fa = u;
        }
        return;
    }
} DSU;

void print(int k) {
    k--;
    if (res[k].cnt == n - 1) {
        std::cout << res[k].sum << '\n';
    } else {
        std::cout << 0 << '\n';
    }
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> option[i].opt;
        if (option[i].opt == _Add) std::cin >> option[i].a >> option[i].b;
        if (option[i].opt == _Delete) std::cin >> option[i].k;
    }
    DSU.Init();
    for (int i = 1; i <= m; i++) {
        if (option[i].opt == _Add) {
            DSU.Union(option[i].a, option[i].b, i);
            print(res.size());
            if (option[i + 1].opt == _Return) DSU.Delete(1);
        }
        if (option[i].opt == _Delete) {
            print(res.size() - option[i].k);
            if (option[i + 1].opt != _Return) DSU.Delete(option[i].k);
        }
        if (option[i].opt == _Return) {
            print(res.size());
        }
    }
    return 0;
}
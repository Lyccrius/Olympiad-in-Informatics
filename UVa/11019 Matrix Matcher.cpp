#include <iostream>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxN = 1000;
const int maxM = 1000;
const int maxX = 100;
const int maxY = 100;

int t;
int n, m;
int x, y;
chr a[maxN + 10][maxM + 10];
chr b[maxX + 10][maxY + 10];
int c[maxN + 10][maxM + 10];
int ans;

struct AhoCosarickAutomaton {
    struct Node {
        int son[30];
        int fail;
        diq index;
    } node[maxX * maxY + 10];

    int ncnt;
    int root;

    void Init() {
        for (int i = 0; i <= ncnt; i++) {
            for (int j = 0; j <= 29; j++) {
                node[i].son[j] = 0;
            }
            node[i].fail = 0;
            node[i].index.clear();
        }
        ncnt = 0;
        return;
    }

    void Build() {
        diq q;
        for (int j = 1; j <= 26; j++) {
            if (node[root].son[j]) {
                q.push_back(node[root].son[j]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int j = 1; j <= 26; j++) {
                if (node[u].son[j]) {
                    node[node[u].son[j]].fail = node[node[u].fail].son[j];
                    q.push_back(node[u].son[j]);
                } else {
                    node[u].son[j] = node[node[u].fail].son[j];
                }
            }
        }
        return;
    }

    void Insert(chr *str, int n, int id) {
        int u = root;
        for (int i = 1; i <= n; i++) {
            int ch = str[i] - 'a' + 1;
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
        }
        node[u].index.push_back(id);
        return;
    }

    void Query(chr *str, int n, int id) {
        int u = root;
        for (int i = 1; i <= n; i++) {
            int ch = str[i] - 'a' + 1;
            u = node[u].son[ch];
            for (auto j : node[u].index) {
                int tx = id - j + 1;
                int ty = i - y + 1;
                if (tx < 1 || tx > n) continue;
                if (ty < 1 || ty > m) continue;
                c[tx][ty]++;
            }
        }
        return;
    }
} ACM;

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[i][j] = 0;
        }
    }
    ans = 0;
    ACM.Init();
    return;
}

void mian() {
    init();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> a[i][j];
        }
    }
    std::cin >> x >> y;
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            std::cin >> b[i][j];
        }
    }
    for (int i = 1; i <= x; i++) ACM.Insert(b[i], y, i);
    ACM.Build();
    for (int i = 1; i <= n; i++) ACM.Query(a[i], m, i);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (c[i][j] == x) {
                ans++;
            }
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
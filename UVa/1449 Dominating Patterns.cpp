#include <iostream>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxN = 150;
const int maxS = 70;
const int maxT = 1e6;

int n;
chr s[maxN + 10][maxS + 10];
chr t[maxT + 10];
int res[maxN + 10];
int ans;

struct AhoCosarickAutomaton {
    struct Node {
        int son[30];
        int fail;
        int index;
        int head;
        int val;
    } node[maxN * maxS + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * maxS + 10];

    int root;
    int ncnt;
    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = node[tail].head;
        node[tail].head = ecnt;
        return;
    }

    void Init() {
        for (int i = 0; i <= ncnt; i++) {
            for (int j = 1; j <= 26; j++) {
                node[i].son[j] = 0;
            }
            node[i].fail = 0;
            node[i].index = 0;
            node[i].head = 0;
            node[i].val = 0;
        }
        ncnt = 0;
        ecnt = 0;
        return;
    }

    void Insert(chr *str, int id) {
        int u = root;
        for (int i = 0; str[i]; i++) {
            int ch = str[i] - 'a' + 1;
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
        }
        node[u].index = id;
        return;
    }

    void Build() {
        diq q;
        for (int i = 1; i <= 26; i++) {
            if (node[root].son[i]) {
                q.push_back(node[root].son[i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int i = 1; i <= 26; i++) {
                if (node[u].son[i]) {
                    node[node[u].son[i]].fail = node[node[u].fail].son[i];
                    q.push_back(node[u].son[i]);
                } else {
                    node[u].son[i] = node[node[u].fail].son[i];
                }
            }
        }
        return;
    }

    void BuildFailTree() {
        for (int u = 1; u <= ncnt; u++) {
            addEdge(node[u].fail, u);
        }
        return;
    }

    void Query(chr *str) {
        int u = root;
        for (int i = 0; str[i]; i++) {
            int ch = str[i] - 'a' + 1;
            u = node[u].son[ch];
            node[u].val++;
        }
        return;
    }

    void DFS(int u) {
        for (int e = node[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v);
            node[u].val += node[v].val;
        }
        res[node[u].index] += node[u].val;
        return;
    }
} ACM;

void mian() {
    ans = 0;
    ACM.Init();
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        ACM.Insert(s[i], i);
        res[i] = 0;
    }
    ACM.Build();
    ACM.BuildFailTree();
    std::cin >> t;
    ACM.Query(t);
    ACM.DFS(ACM.root);
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, res[i]);
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (res[i] == ans) {
            std::cout << s[i] << '\n';
        }
    }
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}
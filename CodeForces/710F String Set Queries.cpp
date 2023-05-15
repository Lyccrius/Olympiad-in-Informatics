#include <iostream>
#include <string>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxM = 3e5;
const int maxS = 3e5;
const int sqrM = 548;

int m;
int t;
chr s[maxS + 10];

namespace ahoCosarickAutomaton {
    struct Node {
        int ch[30];
        int son[30];
        int fail;
        int index;
        int val;
    } node[maxS + 10];

    int ncnt;

    int shift(chr ch) {
        return ch - 'a' + 1;
    }

    void init(int &u) {
        u = ++ncnt;
        return;
    }

    void build(int root) {
        diq q;
        node[root].fail = root;
        for (int i = 1; i <= 26; i++) {
            if (node[root].ch[i]) {
                node[root].son[i] = node[root].ch[i];
                node[node[root].son[i]].fail = root;
                q.push_back(node[root].son[i]);
            } else {
                node[root].son[i] = root;
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            node[u].val = node[node[u].fail].val + node[u].index;
            for (int i = 1; i <= 26; i++) {
                if (node[u].ch[i]) {
                    node[u].son[i] = node[u].ch[i];
                    node[node[u].son[i]].fail = node[node[u].fail].son[i];
                    q.push_back(node[u].son[i]);
                } else {
                    node[u].son[i] = node[node[u].fail].son[i];
                }
            }
        }
        return;
    }

    void insert(int root, chr *s) {
        int u = root;
        for (int i = 0; s[i]; i++) {
            int ch = shift(s[i]);
            if (node[u].ch[ch] == 0) node[u].ch[ch] = ++ncnt;
            u = node[u].ch[ch];
        }
        node[u].index = true;
        return;
    }

    int query(int u, chr *s) {
        int ret = 0;
        for (int i = 0; s[i]; i++) {
            int ch = shift(s[i]);
            u = node[u].son[ch];
            ret += node[u].val;
        }
        return ret;
    }
}

struct AhoCosarickAutomaton {
    int root;

    void Init() {
        ahoCosarickAutomaton::init(root);
        return;
    }

    void Insert(chr *s) {
        ahoCosarickAutomaton::insert(root, s);
        ahoCosarickAutomaton::build(root);
        return;
    }

    int Query(chr *s) {
        return ahoCosarickAutomaton::query(root, s);
    }
} ACM[sqrM + 10][2];

int main() {
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        int j = (i - 1) / sqrM + 1;
        if ((i - 1) % sqrM == 0) {
            ACM[j][0].Init();
            ACM[j][1].Init();
        }
        std::cin >> t >> s;
        if (t == 1) {
            ACM[j][1].Insert(s);
        } else if (t == 2) {
            ACM[j][0].Insert(s);
        } else if (t == 3) {
            int res = 0;
            for (int k = 1; k <= j; k++) {
                res += ACM[k][1].Query(s);
                res -= ACM[k][0].Query(s);
            }
            std::cout << res << '\n';
        }
        std::fflush(stdout);
    }
    return 0;
}
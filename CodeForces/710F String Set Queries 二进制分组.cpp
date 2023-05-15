#include <iostream>
#include <vector>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxM = 3e5;
const int maxS = 3e5;

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

    void init(int &root) {
        root = ++ncnt;
        return;
    }

    void insert(int root, chr *s, int val) {
        int u = root;
        for (int i = 0; s[i]; i++) {
            int ch = shift(s[i]);
            if (node[u].ch[ch] == 0) node[u].ch[ch] = ++ncnt;
            u = node[u].ch[ch];
        }
        node[u].index += val;
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

    int query(int root, chr *s) {
        int u = root;
        int ret = 0;
        for (int i = 0; s[i]; i++) {
            int ch = shift(s[i]);
            u = node[u].son[ch];
            ret += node[u].val;
        }
        return ret;
    }

    int merge(int u, int v) {
        if (!u || !v) return u ^ v;
        node[u].index += node[v].index;
        for (int i = 1; i <= 26; i++) node[u].ch[i] = merge(node[u].ch[i], node[v].ch[i]);
        return u;
    }
}

typedef struct AhoCosarickAutomaton {
    int root;
    int size;

    void Init() {
        ahoCosarickAutomaton::init(root);
        size = 1;
        return;
    }

    void Insert(chr *s) {
        ahoCosarickAutomaton::insert(root, s, 1);
        ahoCosarickAutomaton::build(root);
        return;
    }

    void Delete(chr *s) {
        ahoCosarickAutomaton::insert(root, s, -1);
        ahoCosarickAutomaton::build(root);
    }

    int Query(chr *s) {
        return ahoCosarickAutomaton::query(root, s);
    }
} acm;

std::vector<acm> ACM;

void create() {
    ACM.push_back(acm());
    ACM.back().Init();
    return;
}

void update() {
    while (ACM.size() >= 2 && ACM[ACM.size() - 1].size == ACM[ACM.size() - 2].size) {
        acm a = ACM.back(); ACM.pop_back();
        acm b = ACM.back(); ACM.pop_back();
        acm c = (acm) {ahoCosarickAutomaton::merge(a.root, b.root), a.size + b.size};
        ahoCosarickAutomaton::build(c.root);
        ACM.push_back(c);
    }
    return;
}

void add(chr *s) {
    create();
    ACM.back().Insert(s);
    update();
    return;
}

void del(chr *s) {
    create();
    ACM.back().Delete(s);
    update();
    return;
}

void ask(chr *s) {
    int res = 0;
    for (auto i : ACM) res += i.Query(s);
    std::cout << res << '\n';
    return;
}

int main() {
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> t >> s;
        if (t == 1) add(s);
        else if (t == 2) del(s);
        else if (t == 3) ask(s);
        fflush(stdout);
    }
    return 0;
}
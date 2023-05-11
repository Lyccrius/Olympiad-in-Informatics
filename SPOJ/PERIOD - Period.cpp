#include <iostream>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxN = 1e6;

int t;
int n;
chr s[maxN + 10];
int kase;

struct AhoCosarickAutomaton {
    struct Node {
        int son[30];
        int fail;
        int index;
    } node[maxN + 10];

    int ncnt;
    int root;

    void Init() {
        for (int i = 0; i <= ncnt; i++) {
            for (int j = 1; j <= 26; j++) {
                node[i].son[j] = 0;
            }
            node[i].fail = 0;
        }
        ncnt = 0;
        return;
    }

    void Insert(chr *str) {
        int u = root;
        for (int i = 1; str[i]; i++) {
            int ch = str[i] - 'a' + 1;
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
        }
        node[u].index = true;
        return;
    }

    void Build() {
        diq q;
        for (int i = 1; i <= 26; i++) if (node[root].son[i]) q.push_back(node[root].son[i]);
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

    void Query(chr *str) {
        int u = 0;
        for (int i = 1; str[i]; i++) {
            int ch = str[i] - 'a' + 1;
            u = node[u].son[ch];
            if (node[u].fail && i % (i - node[u].fail) == 0) {
                std::cout << i << ' ' << i / (i - node[u].fail) << '\n';
            }
        }
        return;
    }
} ACM;

void mian() {
    std::cin >> n;
    std::cin >> (s + 1);
    std::cout << "Test case #" << ++kase << '\n';
    ACM.Init();
    ACM.Insert(s);
    ACM.Build();
    ACM.Query(s);
    std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
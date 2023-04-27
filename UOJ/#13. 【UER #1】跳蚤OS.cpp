#include <iostream>
#include <string>
#include <map>

typedef std::string str;
typedef std::map<str, int> msi;

const int maxN = 2e4;
const int maxM = 10;

int n, m;
str s, t;
str p;

struct Trie {
    struct Node {
        str path;
        msi son;
        int cur;

        Node() {
            son[""] = 1;
            return;
        }
    } node[maxN * 40 + 10];

    int ncnt;
    int root;

    int get(str s) {
        //printf("\n\n");
        //printf("geting "); std::cout << s; printf("\n");
        int ret = root;
        str now;
        now.clear();
        for (int i = 1; i <= s.size(); i++) {
            if (i == s.size() || s[i] == '/') {
                //printf("now = "); std::cout << now; printf("\n");
                if (node[ret].son[now] == 0) {
                    node[ret].son[now] = ++ncnt;
                    node[node[ret].son[now]].path = node[ret].path;
                    //node[node[ret].son[now]].path = node[ret].path + '/' + now;
                    if (ret != root) {
                        //printf("ret = %d, son = %d, add div\n", ret, ncnt);
                        node[node[ret].son[now]].path += '/';
                    }
                    node[node[ret].son[now]].path += now;
                    //if (i != s.size()) node[node[ret].son[now]].path += '/';
                    //printf("node[%d] = ", ncnt); std::cout << node[ncnt].path; printf("\n");
                }
                ret = node[ret].son[now];
                while (node[ret].cur) ret = node[ret].cur;
                now.clear();
            } else {
                now.push_back(s[i]);
            }
        }
        return ret;
    }

    void Init() {
        root = ++ncnt;
        node[root].path = '/';
        return;
    }

    void Add(str s, str t) {
        int ns = get(s);
        int nt = get(t);
        if (ns != nt) node[ns].cur = nt;
        //printf("%d cur to %d\n", ns, nt);
        //std::cout << node[ns].path << " cur to " << node[nt].path << '\n';
        return;
    }

    void Ask(str p) {
        int np = get(p);
        std::cout << node[np].path << '\n';
        return;
    }
} T;

int main() {
    T.Init();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> s >> t;
        T.Add(s, t);
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> p;
        T.Ask(p);
    }
    return 0;
}
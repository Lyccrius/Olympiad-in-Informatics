#include <iostream>

const int maxM = 5e4;
const int maxN = 5e4;
const int maxA = 5e5;

int M, N;
int b[maxM + 10];
int c[maxN + 10];
int a[maxA + 10];

struct TrieTree {
    struct Node {
        int son[2];
        int val;
        int sum;
    } node[maxA * 2 + 10];

    int ncnt;
    int root;

    void Init() {
        root = ++ncnt;
        return;
    }

    void Insert(int n) {
        int u = root;
        for (int i = 1; i <= n; i++) {
            if (node[u].son[a[i]] == 0) node[u].son[a[i]] = ++ncnt;
            u = node[u].son[a[i]];
            //printf("a[%d] = %d, u = %d\n", i, a[i], u);
        }
        node[u].val++;
        return;
    }

    void PushUp(int u) {
        if (node[u].son[0]) PushUp(node[u].son[0]);
        if (node[u].son[1]) PushUp(node[u].son[1]);
        node[u].sum += node[node[u].son[0]].val;
        node[u].sum += node[node[u].son[0]].sum;
        node[u].sum += node[node[u].son[1]].val;
        node[u].sum += node[node[u].son[1]].sum;
        //printf("PushUp(%d) = %d\n", u, node[u].sum);
        return;
    }

    int Query(int n) {
        int u = root;
        int ret = 0;
        for (int i = 1; i <= n; i++) {
            if (node[u].son[a[i]] == 0) return ret;
            u = node[u].son[a[i]];
            ret += node[u].val;
        }
        ret += node[u].sum;
        return ret;
    }
} TT;

int ans;

int main() {
    std::cin >> M >> N;
    TT.Init();
    for (int i = 1; i <= M; i++) {
        std::cin >> b[i];
        for (int j = 1; j <= b[i]; j++) std::cin >> a[j];
        TT.Insert(b[i]);
    }
    TT.PushUp(TT.root);
    for (int i = 1; i <= N; i++) {
        std::cin >> c[i];
        for (int j = 1; j <= c[i]; j++) std::cin >> a[j];
        std::cout << TT.Query(c[i]) << '\n';
    }
    //std::cout << ans;
    return 0;
}
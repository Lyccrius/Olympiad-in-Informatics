#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 5e5;
const int maxK = 1e5;
const int maxP = 31;

int n, k;
lxl a[maxN + 10];
lxl x[maxN + 10];
struct Node {
    int rank;
    int head;
    lxl weight;

    bool operator<(const Node &other) const {
        return weight < other.weight;
    }
} node[maxN + 10];
std::priority_queue<Node> q;
lxl ans;

struct TrieTree {
    struct Node {
        int next[2];
        int size;
    } node[maxN * (maxP + 1) + 10];

    int ncnt;

    void Insert(lxl val) {
        int u = 0;
        for (int p = maxP; p >= 0; p--) {
            int i = (val >> p) & 1;
            if (node[u].next[i] == 0) {
                node[u].next[i] = ++ncnt;
            }
            u = node[u].next[i];
            node[u].size++;
        }
        return;
    }

    lxl Query(lxl val, int t) {
        lxl ret = 0;
        int u = 0;
        for (int p = maxP; p >= 0; p--) {
            int i = (val >> p) & 1;
            if (node[node[u].next[i ^ 1]].size >= t) {
                u = node[u].next[i ^ 1];
                ret |= 1ll << p;
            } else {
                t -= node[node[u].next[i ^ 1]].size;
                u = node[u].next[i];
            }
        }
        return ret;
    }
} TT;

int main() {
    promote();
    std::cin >> n >> k, k *= 2;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) x[i] = x[i - 1] ^ a[i];
    for (int i = 0; i <= n; i++) TT.Insert(x[i]);
    for (int i = 0; i <= n; i++) {
        node[i] = (Node) {i, 1, TT.Query(x[i], 1)};
        q.push(node[i]);
    }
    for (int i = 1; i <= k; i++) {
        Node t = q.top();
        q.pop();
        ans += t.weight;
        node[t.rank].head++;
        node[t.rank].weight = TT.Query(x[t.rank], node[t.rank].head);
        q.push(node[t.rank]);
    }
    ans /= 2;
    std::cout << ans << '\n';
    return 0;
}
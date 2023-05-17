#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef std::vector<int > vic;

const int maxN = 500;
const int maxQ = 6e4;
const int maxA = 1e9;

int n, q;
int a[maxN + 10][maxN + 10];
int b[maxN + 10][maxN + 10];
int x_1, y_1, x_2, y_2, k;
int ans[maxQ + 10];
vic raw;

struct Node {
    int x, y;
    int val;

    bool operator<(const Node &other) const {
        return val < other.val;
    }
};

std::deque<Node> nodes;

struct Query {
    int i;
    int x_1, y_1;
    int x_2, y_2;
    int k;
};

std::deque<Query> querys;

int lowbit(int x) {
    return x & -x;
}

struct BinaryIndexedTree2 {
    struct BinaryIndexedTree1 {
        struct Node {
            int val;
        } node[maxN + 10];

        void Add(int pos, int val) {
            while (pos <= n) {
                node[pos].val += val;
                pos += lowbit(pos);
            }
            return;
        }

        int Ask(int pos) {
            int ret = 0;
            while (pos >= 1) {
                ret += node[pos].val;
                pos -= lowbit(pos);
            }
            return ret;
        }

        int Ask(int l, int r) {
            return Ask(r) - Ask(l - 1);
        }

        void Show() {
            for (int i = 1; i <= n; i++) printf("%d ", node[i].val);
            printf("\n");
        }
    } BIT1[maxN + 10];

    void Add(int x, int y, int val) {
        while (x <= n) {
            BIT1[x].Add(y, val);
            x += lowbit(x);
        }
        return;
    }

    int Ask(int pos, int l, int r) {
        int ret = 0;
        while (pos >= 1) {
            ret += BIT1[pos].Ask(l, r);
            pos -= lowbit(pos);
        }
        return ret;
    }

    int Ask(int x1, int y1, int x2, int y2) {
        return Ask(x2, y1, y2) - Ask(x1 - 1, y1, y2);
    }

    void Show() {
        for (int i = 1; i <= n; i++) BIT1[i].Show();
        printf("\n");
        return;
    }
} BIT2;

void solve(int l, int r, std::deque<Query> q) {
    if (l == r) {
        for (int i = 0; i < q.size(); i++) ans[q[i].i] = l;
        return;
    }
    std::deque<Query> ql;
    std::deque<Query> qr;
    int mid = (l + r) / 2;
    for (int i = l; i <= mid; i++) BIT2.Add(nodes[i].x, nodes[i].y, 1);
    for (int i = 0; i < q.size(); i++) {
        int x_1 = q[i].x_1;
        int y_1 = q[i].y_1;
        int x_2 = q[i].x_2;
        int y_2 = q[i].y_2;
        int t = BIT2.Ask(x_1, y_1, x_2, y_2);
        if (t >= q[i].k) ql.push_back(q[i]);
        else q[i].k -= t, qr.push_back(q[i]);
    }
    for (int i = l; i <= mid; i++) BIT2.Add(nodes[i].x, nodes[i].y, -1);
    if (ql.size()) solve(l, mid, ql);
    if (qr.size()) solve(mid + 1, r, qr);
    return;
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) nodes.push_back((Node) {i, j, a[i][j]});
    std::sort(nodes.begin(), nodes.end());
    for (int i = 1; i <= q; i++) {
        std::cin >> x_1 >> y_1 >> x_2 >> y_2 >> k;
        querys.push_back((Query) {i, x_1, y_1, x_2, y_2, k});
    }
    solve(0, nodes.size() - 1, querys);
    for (int i = 1; i <= q; i++) std::cout << nodes[ans[i]].val << '\n';
    return 0;
}
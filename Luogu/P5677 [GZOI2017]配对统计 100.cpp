#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 3e5;
const int maxM = 3e5;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int l, r;
int res;
lxl ans;

struct Node {
    int a;
    int i;

    bool operator<(const Node &other) const {
        return a < other.a;
    }
};

struct Unite {
    int l;
    int r;

    bool operator<(const Unite &other) const {
        return r < other.r;
    }
};

struct Query {
    int i;
    int l;
    int r;

    bool operator<(const Query &other) const {
        return r < other.r;
    }
};

std::deque<Node> nodes;
std::deque<Unite> unites;
std::deque<Query> querys;

Unite makeUnite(int l, int r) {
    return (Unite) {std::min(l, r), std::max(l, r)};
}

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN + 10];

    int lowbit(int x) {
        return x & - x;
    }

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
} BIT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) nodes.push_back((Node) {a[i], i});
    std::sort(nodes.begin(), nodes.end());
    for (int i = 0; i < nodes.size(); i++) {
        if (i == 0 && i == nodes.size() - 1) continue;
        if (i == 0) {
            unites.push_back(makeUnite(nodes[i].i, nodes[i + 1].i));
            continue;
        }
        if (i == nodes.size() - 1) {
            unites.push_back(makeUnite(nodes[i - 1].i, nodes[i].i));
            continue;
        }
        int dl = nodes[i].a - nodes[i - 1].a;
        int dr = nodes[i + 1].a - nodes[i].a;
        if (dl <= dr) {
            unites.push_back(makeUnite(nodes[i - 1].i, nodes[i].i));
        }
        if (dl >= dr) {
            unites.push_back(makeUnite(nodes[i].i, nodes[i + 1].i));
        }
    }
    std::sort(unites.begin(), unites.end());
    for (int i = 1; i <= m; i++) std::cin >> l >> r, querys.push_back((Query) {i, l, r});
    std::sort(querys.begin(), querys.end());
    for (auto query : querys) {
        while (unites.size() && unites.front().r <= query.r) {
            BIT.Add(unites.front().l, 1);
            unites.pop_front();
        }
        ans += 1ll * (BIT.Ask(query.r) - BIT.Ask(query.l - 1)) * query.i;
    }
    std::cout << ans;
    return 0;
}
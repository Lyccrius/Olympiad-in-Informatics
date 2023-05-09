#include <iostream>
#include <algorithm>
#include <deque>

const int maxN = 2e6;
const int maxC = 2e6;
const int maxM = 2e6;

int n, c, m;
int x[maxN + 10];
int l, r;
int pre1[maxC + 10];
int pre2[maxC + 10];
int ans[maxM + 10];

struct Query {
    int i;
    int l, r;

    bool operator<(Query other) const {
        return r < other.r;
    }
};
std::deque<Query> querys;

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN + 10];

    int lowbit(int x) {
        return x & (- x);
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
} BIT;int main() {
    std::cin >> n >> c >> m;
    for (int i = 1; i <= n; i++) std::cin >> x[i];
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r;
        querys.push_back((Query) {i, l, r});
    }
    std::sort(querys.begin(), querys.end());
    for (int i = 1; i <= n; i++) {
        if (!pre2[x[i]]) {
            pre2[x[i]] = i;
        } else if (!pre1[x[i]]) {
            BIT.Add(pre2[x[i]], 1);
            pre1[x[i]] = i;
        } else {
            BIT.Add(pre2[x[i]], -1);
            BIT.Add(pre1[x[i]], 1);
            pre2[x[i]] = pre1[x[i]];
            pre1[x[i]] = i;
        }
        while (querys.size() && querys.front().r <= i) {
            ans[querys.front().i] = BIT.Ask(querys.front().r) - BIT.Ask(querys.front().l - 1);
            querys.pop_front();
        }
    }
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}
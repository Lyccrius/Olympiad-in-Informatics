#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e6;
const int maxM = 1e6;

int n;
int a[maxN + 10];
int m;

struct Query {
    int id;
    int l, r;

    bool operator<(const Query &other) const {
        return r < other.r;
    }
} query[maxM + 10];

int last[maxN + 10];
int ans[maxM + 10];

struct BinaryIndexedTree {
    int node[maxN + 10];

    int lowbit(int val) {
        return val & -val;
    }

    void Add(int pos, int val) {
        while (pos <= n) {
            node[pos] += val;
            pos += lowbit(pos);
        }
        return;
    }

    int Ask(int pos) {
        int ret = 0;
        while (pos >= 1) {
            ret += node[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
} BIT;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::cin >> m;
    for (int i = 1; i <= m; i++) std::cin >> query[i].l >> query[i].r, query[i].id = i;
    std::sort(query + 1, query + m + 1);
    int i = 1;
    int j = 1;
    int k = 1;
    for (i = 1; i <= m; i++) {
        for (j = k; j <= query[i].r; j++) {
            if (last[a[j]]) BIT.Add(last[a[j]], -1);
            BIT.Add(j, 1);
            last[a[j]] = j;
        }
        ans[query[i].id] = BIT.Ask(query[i].r) - BIT.Ask(query[i].l - 1);
        k = query[i].r + 1;
    }
    for (i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}
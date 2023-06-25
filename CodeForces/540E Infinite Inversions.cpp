#include <iostream>
#include <map>

typedef long long lxl;
typedef std::map<int, int> mii;

const int maxN = 1e5;

int n;
int a, b;
mii m;
mii r;
int t;
lxl ans;

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[2 * maxN + 10];

    int lowbit(int x) {
        return x & - x;
    }

    void add(int pos) {
        while (pos <= 2 * n) {
            node[pos].val++;
            pos += lowbit(pos);
        }
        return;
    }

    int ask(int pos) {
        int ret = 0;
        while (pos) {
            ret += node[pos].val;
            pos -= lowbit(pos);
        }
        return ret;
    }
} bit;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a >> b;
        if (!m[a]) m[a] = a;
        if (!m[b]) m[b] = b;
        std::swap(m[a], m[b]);
    }
    for (auto i : m) r[i.first] = ++t;
    for (auto i : m) {
        a = i.first;
        b = i.second;
        ans += std::abs(a - b - (r[a] - r[b]));
        ans += r[a] - bit.ask(r[b]) - 1;
        bit.add(r[b]);
    }
    std::cout << ans << '\n';
    return 0;
}
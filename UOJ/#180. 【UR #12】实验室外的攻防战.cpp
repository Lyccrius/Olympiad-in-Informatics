#include <iostream>

const int maxN = 1e5;

int n;
int a[maxN + 10];
int b[maxN + 10];
int p[maxN + 10];

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN + 10];

    int lowbit(int x) {
        return x & - x;
    }

    void Add(int pos, int val) {
        while (pos >= 1) {
            node[pos].val = std::max(node[pos].val, val);
            pos -= lowbit(pos);
        }
        return;
    }

    int Ask(int pos) {
        int ret = 0;
        while (pos <= n) {
            ret = std::max(ret, node[pos].val);
            pos += lowbit(pos);
        }
        return ret;
    }
} BIT;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) p[a[i]] = i;
    for (int i = 1; i <= n; i++) {
        if (BIT.Ask(p[b[i]]) > b[i]) {
            std::cout << "NO" << '\n';
            return 0;
        }
        BIT.Add(p[b[i]], b[i]);
    }
    std::cout << "YES" << '\n';
    return 0;
}
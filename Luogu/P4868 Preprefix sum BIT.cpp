#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;

int N, M;
lxl a[maxN + 10];
char opt[10];
int p;
lxl x;

struct BinaryIndexedTree {
    struct Node {
        lxl val;
    } node[maxN + 10];

    int LowBit(int val) {
        return val & -val;
    }

    void Add(int pos, lxl val) {
        while (pos <= N) {
            node[pos].val += val;
            pos += LowBit(pos);
        }
        return;
    }

    lxl Ask(int pos) {
        lxl ret = 0;
        while (pos > 0) {
            ret += node[pos].val;
            pos -= LowBit(pos);
        }
        return ret;
    }
} S, SS;

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) S.Add(i, a[i]);
    for (int i = 1; i <= N; i++) SS.Add(i, a[i] * i);
    for (int i = 1; i <= M; i++) {
        std::cin >> opt;
        if (opt[0] == 'M') std::cin >> p >> x, S.Add(p, x - a[p]), SS.Add(p, (x - a[p]) * p), a[p] = x;
        else std::cin >> p, std::cout << S.Ask(p) * (p + 1) - SS.Ask(p) << '\n';
    }
    return 0;
}
#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 2e5;
const int maxM = 2e5;
const int sqrN = 447;
const int mod = 1e9 + 7;

int n, m;
int a[maxN + 10];
int opt;
int x, y, z;
int l, r;

struct BlockArrayVal {
    struct Block {
        int l, r;
        lxl val;
    } block[100000 + 10];

    struct Array {
        lxl val;
        int bel;
    } array[maxN + 10];

    void Build() {
        for (int i = 1; i <= n; i++) array[i].val = a[i];
        for (int i = 1; i <= n; i++) array[i].bel = (i - 1) / sqrN + 1;
        for (int i = 1; i <= n; i++) block[array[i].bel].val += array[i].val;
        for (int i = 1; i <= n; i++) block[array[i].bel].r = i;
        for (int i = n; i >= 1; i--) block[array[i].bel].l = i;
        return;
    }

    void Add(int pos, int val) {
        array[pos].val += val;
        block[array[pos].bel].val += val;
        return;
    }

    lxl Ask(int l, int r) {
        lxl ret = 0;
        if (array[l].bel == array[r].bel) {
            for (int i = l; i <= r; i++) ret += array[i].val;
        } else {
            for (int i = array[l].bel + 1; i <= array[r].bel - 1; i++) ret += block[i].val;
            for (int i = l; i <= block[array[l].bel].r; i++) ret += array[i].val;
            for (int i = block[array[r].bel].l; i <= r; i++) ret += array[i].val;
        }
        return ret;
    }
} val;

struct BlockArrayTag {
    lxl tag[sqrN + 10];

    void Add(int gap, int pos, int val) {
        for (int i = pos; i <= gap; i++) tag[i] += val;
        return;
    }

    lxl Ask(int gap, int pos) {
        return tag[pos % gap] + tag[gap] * (pos / gap);
    }

    lxl Ask(int gap, int l, int r) {
        return Ask(gap, r) - Ask(gap, l - 1);
    }
} tag[sqrN + 10];

void add() {
    std::cin >> x >> y >> z;
    if (x <= sqrN) {
        tag[x].Add(x, y, z);
    } else {
        for (int i = y; i <= n; i += x) val.Add(i, z);
    }
    return;
}

void ask() {
    std::cin >> l >> r;
    lxl res = val.Ask(l, r);
    for (int i = 1; i <= sqrN; i++) res += tag[i].Ask(i, l, r);
    std::cout << res % mod << '\n';
    return;
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    val.Build();
    for (int i = 1; i <= m; i++) {
        std::cin >> opt;
        if (opt == 1) add();
        else if (opt == 2) ask();
    }
    return 0;
}
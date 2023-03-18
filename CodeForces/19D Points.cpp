#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef char chr;
typedef std::vector<int> vic;
typedef std::set<int> sic;

const int maxN = 2e5 + 10;

int n;

struct Option {
    chr type[10];
    int x, y;
} option[maxN + 10];

vic rawX;
vic rawY;

sic s[maxN + 10];

struct SegmentTree {
    struct Node {
        int val;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        node[u].val = std::max(node[u * 2].val, node[u * 2 + 1].val);
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    void Update(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val = std::max(node[u].val, val);
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Update(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Update(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int pos, int val) {
        if (l == r) {
            if (node[u].val > val) {
                return l;
            } else {
                return 0;
            }
        }
        int ret = 0;
        int mid = (l + r) / 2;
        if (pos <= mid && node[u * 2].val > val) ret = Query(u * 2, l, mid, pos, val);
        if (ret) return ret;
        if (node[u * 2 + 1].val > val) ret = Query(u * 2 + 1, mid + 1, r, pos, val);
        return ret;
    }
} SGT;

void add(int x, int y) {
    s[x].insert(y);
    SGT.Update(1, 1, rawX.size(), x, y);
    return;
}

void remove(int x, int y) {
    s[x].erase(s[x].find(y));
    SGT.Modify(1, 1, rawX.size(), x, *s[x].rbegin());
    return;
}

void find(int x, int y) {
    int pos = SGT.Query(1, 1, rawX.size(), x + 1, y);
    if (pos) {
        std::cout << rawX[pos - 1] << ' ' << rawY[*s[pos].upper_bound(y) - 1] << '\n';
    } else {
        std::cout << - 1 << '\n';
    }
    return;
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> option[i].type >> option[i].x >> option[i].y;
    for (int i = 1; i <= n; i++) rawX.push_back(option[i].x);
    for (int i = 1; i <= n; i++) rawY.push_back(option[i].y);
    rawX.push_back(maxN + 10);
    rawY.push_back(maxN + 10);
    std::sort(rawX.begin(), rawX.end());
    std::sort(rawY.begin(), rawY.end());
    rawX.erase(std::unique(rawX.begin(), rawX.end()), rawX.end());
    rawY.erase(std::unique(rawY.begin(), rawY.end()), rawY.end());
    for (int i = 1; i <= rawX.size(); i++) s[i].insert(0);
    for (int i = 1; i <= n; i++) option[i].x = std::lower_bound(rawX.begin(), rawX.end(), option[i].x) - rawX.begin() + 1;
    for (int i = 1; i <= n; i++) option[i].y = std::lower_bound(rawY.begin(), rawY.end(), option[i].y) - rawY.begin() + 1;
    for (int i = 1; i <= n; i++) {
        if (option[i].type[0] == 'a') add(option[i].x, option[i].y);
        else if (option[i].type[0] == 'r') remove(option[i].x, option[i].y);
        else if (option[i].type[0] == 'f') find(option[i].x, option[i].y);
    }
    return 0;
}
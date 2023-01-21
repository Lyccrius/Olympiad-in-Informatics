#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::pair<int, int> pii;

const int maxN = 2e5;

int n;
char ch;
int s[maxN + 10];
int a[maxN + 10];
int v[maxN + 10];

struct Node {
    int val;
    int l, r;

    bool operator<(const Node &other) const {
        if (val != other.val) return val > other.val;
        if (l != other.l) return l > other.l;
        return r > other.r;
    }
};

std::priority_queue<Node> q;
std::vector<pii> ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> ch;
        if (ch == 'B') s[i] = 1;
        else s[i] = 0;
    }
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i < n; i++) if (s[i] ^ s[i + 1]) q.push((Node) {std::abs(a[i] - a[i + 1]), i, i + 1});
    while (!q.empty()) {
        Node node = q.top();
        q.pop();
        int l = node.l;
        int r = node.r;
        if (v[l] || v[r]) continue;
        v[l] = true;
        v[r] = true;
        ans.push_back(std::make_pair(l, r));
        while (v[l] && l >= 1) l--;
        while (v[r] && r <= n) r++;
        if ((1 <= l) && (r <= n) && (s[l] != s[r])) q.push((Node) {std::abs(a[l] - a[r]), l, r});
    }
    std::cout << ans.size() << '\n';
    for (auto i : ans) std::cout << i.first << ' ' << i.second << '\n';
    return 0;
}
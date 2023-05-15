#include <iostream>
#include <queue>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int a, b, c;
lxl s;

struct Node {
    int val;
    int cnt;

    bool operator<(const Node &other) const {
        return val > other.val;
    }
};

std::priority_queue<Node> q;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a;
        q.push((Node) {a, 1});
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> b >> c;
        int x = 0;
        while (q.top().val < c && b) {
            Node t = q.top();
            q.pop();
            if (b >= t.cnt) {
                b -= t.cnt;
                x += t.cnt;
            } else {
                q.push((Node) {c, b});
                q.push((Node) {t.val, t.cnt - b});
                b = 0;
            }
        }
        if (x) {
            q.push((Node) {c, x});
        }
    }
    while (q.size()) {
        s += 1ll * q.top().cnt * q.top().val;
        q.pop();
    }
    std::cout << s << '\n';
    return 0;
}
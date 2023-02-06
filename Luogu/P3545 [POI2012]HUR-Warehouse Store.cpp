#include <iostream>
#include <queue>
#include <vector>
#include <stack>

typedef long long lxl;

const lxl maxN = 2.5e5;

lxl n;
lxl a[maxN + 10];
lxl b[maxN + 10];

struct Node {
    lxl i;
    lxl a;

    bool operator<(const Node &other) const {
        if (a != other.a) return a > other.a;
        return i > other.i;
    }
};

std::priority_queue<Node> q;
std::stack<Node> ans;

//lxl cnt = 1;

int main() {
    std::cin >> n;
    for (lxl i = 1; i <= n; i++) std::cin >> a[i];
    for (lxl i = 1; i <= n; i++) std::cin >> b[i];
    for (lxl i = n; i >= 1; i--) {
        //for (lxl i = 1; i <= cnt; i++) prlxlf("    ");
        //prlxlf("round #%d: %d, %d\n", i, a[i], b[i]);
        //cnt++;
        q.push((Node) {i, b[i]});
        while (!q.empty() && a[i]) {
            //for (lxl i = 1; i <= cnt; i++) prlxlf("    ");
            //prlxlf("now a = %d\n", a[i]);
            Node t = q.top();
            q.pop();
            //or (lxl i = 1; i <= cnt; i++) prlxlf("    ");
            //prlxlf("considering #%d, %d\n", t.i, t.a);
            //cnt++;
            if (a[i] >= t.a) {
                //for (lxl i = 1; i <= cnt; i++) prlxlf("    ");
                //prlxlf("ok\n");
                a[i] -= t.a;
                ans.push(t);
            } else {
                //for (lxl i = 1; i <= cnt; i++) prlxlf("    ");
                //prlxlf("no\n");
                t.a -= a[i];
                q.push(t);
                a[i] = 0;
                //for (lxl i = 1; i <= cnt; i++) prlxlf("    ");
                //prlxlf("push %d, %d\n", t.i, t.a);
            }
            //cnt--;
        }
        //cnt--;
    }
    std::cout << ans.size() << '\n';
    while (!ans.empty()) {
        std::cout << ans.top().i << ' ';
        ans.pop();
    }
    return 0;
}
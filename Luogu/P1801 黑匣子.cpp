#include <iostream>
#include <queue>
#include <vector>

const int maxN = 2e5;
const int maxM = 2e5;

int m, n;
int a[maxM + 10];
int u[maxN + 10];
int v[maxM + 10];

struct BlackBox {
    std::priority_queue<int, std::vector<int>, std::less<int> > his;
    std::priority_queue<int, std::vector<int>, std::greater<int> > now;

    void ADD(int x) {
        if (his.empty()) {
            now.push(x);
            return;
        }
        if (his.top() > x) {
            now.push(his.top());
            his.pop();
            his.push(x);
        } else {
            now.push(x);
        }
        return;
    }

    int GET() {
        his.push(now.top());
        now.pop();
        return his.top();
    }
} BB;

int main() {
    std::cin >> m >> n;
    for (int i = 1; i <= m; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> u[i];
    for (int i = 1; i <= n; i++) v[u[i]] ++;
    for (int i = 1; i <= m; i++) {
        BB.ADD(a[i]);
        while (v[i]) {
            v[i]--;
            std::cout << BB.GET() << '\n';
        }
    }
    return 0;
}
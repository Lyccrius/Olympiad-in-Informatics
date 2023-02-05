#include <iostream>
#include <queue>
#include <vector>

typedef long long lxl;

const lxl maxN = 2e5;

lxl t;

lxl n, c;
lxl a[maxN + 10];

void mian() {
    std::priority_queue<lxl, std::vector<lxl>, std::greater<lxl> > q;
    std::cin >> n >> c;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) q.push(i + a[i]);
    lxl ans = 0;
    while (!q.empty()) {
        if (c >= q.top()) {
            c -= q.top();
            q.pop();
            ans++;
        } else break;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
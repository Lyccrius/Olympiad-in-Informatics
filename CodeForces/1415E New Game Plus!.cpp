#include <iostream>
#include <algorithm>
#include <queue>

typedef long long lxl;
typedef std::priority_queue<lxl> prl;

const int maxN = 5e5;

int n, k;
int c[maxN + 10];
prl q;
lxl ans;

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= k; i++) q.push(0); q.push(0);
    std::sort(c + 1, c + n + 1);
    std::reverse(c + 1, c + n + 1);
    for (int i = 1; i <= n; i++) {
        lxl sum = q.top(); q.pop();
        ans += sum;
        sum += c[i];
        q.push(sum);
    }
    std::cout << ans;
    return 0;
}
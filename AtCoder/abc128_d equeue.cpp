#include <iostream>
#include <queue>

typedef std::priority_queue<int> pri;

const int maxN = 50;
const int maxK = 100;

int n, k;
int v[maxN + 10];
int ans;

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> v[i];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; i + j <= std::min(n, k); j++) {
            pri q;
            int res = 0;
            for (int i_ = 1; i_ <= i; i_++) q.push(v[i_]);
            for (int j_ = n; j_ >= n - j + 1; j_--) q.push(v[j_]);
            while (q.size() && (q.top() > 0 || q.size() > k - i - j)) res += q.top(), q.pop();
            ans = std::max(ans, res);
        }
    }
    std::cout << ans << '\n';
    return 0;
}
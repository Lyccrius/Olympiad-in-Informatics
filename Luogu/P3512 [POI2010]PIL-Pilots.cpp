#include <iostream>
#include <deque>

typedef long long lxl;

const lxl maxK = 2e9;
const lxl maxN = 3e6;

lxl k, n;
lxl a[maxN + 10];

int main() {
    std::cin >> k >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::deque<lxl> mx;
    std::deque<lxl> mn;
    lxl ans = 0;
    lxl cur = 1;
    for (lxl i = 1; i <= n; i++) {
        while (!mx.empty() && a[mx.back()] < a[i]) mx.pop_back();
        while (!mn.empty() && a[mn.back()] > a[i]) mn.pop_back();
        mx.push_back(i);
        mn.push_back(i);
        while (!mx.empty() && !mn.empty() && a[mx.front()] - a[mn.front()] > k) {
            cur++;
            while (!mx.empty() && mx.front() < cur) mx.pop_front();
            while (!mn.empty() && mn.front() < cur) mn.pop_front();
        }
        ans = std::max(ans, i - cur + 1);
    }
    std::cout << ans;
    return 0;
}
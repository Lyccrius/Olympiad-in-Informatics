#include <iostream>
#include <algorithm>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 2000;

int n;
int a[maxN + 10];
int b[maxN + 10];
diq p;
diq q;
int ans;

void mian() {
    ans = 0;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) p.push_back(a[i]);
    for (int i = 1; i <= n; i++) q.push_back(b[i]);
    std::sort(p.begin(), p.end());
    std::sort(q.begin(), q.end());
    for (int i = 1; i <= n; i++) {
        if (p.back() > q.back()) {
            p.pop_back();
            q.pop_back();
            ans += 200;
        } else if (p.front() > q.front()) {
            p.pop_front();
            q.pop_front();
            ans += 200;
        } else if (p.front() < q.back()) {
            p.pop_front();
            q.pop_back();
            ans -= 200;
        } else {
            p.pop_back();
            q.pop_back();
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}
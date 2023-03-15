#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1000;

int n;
vic num;
int lim;
int ans;

bool IDS(int now, int top) {
    if (num[now] == n) {
        ans = now;
        return true;
    }
    if (now >= lim) return false;
    if ((top << (lim - now)) < n) return false;
    for (int i = now; i >= 0; i--) {
        num.push_back(num[now] + num[i]);
        if (IDS(now + 1, std::max(top, num[now] + num[i]))) return true;
        num.pop_back();
        num.push_back(num[now] - num[i]);
        if (IDS(now + 1, std::max(top, num[now] - num[i]))) return true;
        num.pop_back();
    }
    return false;
}

void mian() {
    lim = 0;
    num.clear();
    num.push_back(1);
    while (true) {
        if (IDS(0, 1)) {
            break;
        }
        lim++;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}
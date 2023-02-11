#include <iostream>
#include <vector>
#include <algorithm>

int t;

const int maxN = 300;

int n;
int a[maxN + 10];

void mian() {
    std::vector<int> j, o;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        if (a[i] & 1) j.push_back(i);
        else o.push_back(i);
    }
    if ((n == 3 && j.size() == 2) || j.size() == 0) {
        std::cout << "NO\n";
        return;
    }
    int cnt = 0;
    std::vector<int> ans;
    std::cout << "YES\n";
    if (j.size() < 3) {
        ans.push_back(j[0]);
        ans.push_back(o[0]);
        ans.push_back(o[1]);
    } else {
        ans.push_back(j[0]);
        ans.push_back(j[1]);
        ans.push_back(j[2]);
    }
    std::sort(ans.begin(), ans.end());
    for (auto i : ans) std::cout << i << ' ';
    std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 1e6;
const lxl maxK = 1e18;

int n;
lxl k;
int x[maxN + 10];
int y[maxN + 10];
int s[maxN + 10];

namespace S1 {
    const int maxN = 20;

    bool is() {
        return n <= 20;
    }

    bool a[maxN + 10][maxN + 10];
    std::deque<vic> SS;

    void DFS(int now, vic S) {
        if (now >= n) {
            if (S.size()) {
                SS.push_back(S);
            }
            return;
        }
        DFS(now + 1, S);
        for (auto i : S) {
            if (a[i][now]) {
                return;
            }
        }
        S.push_back(now);
        DFS(now + 1, S);
        return;
    }

    bool cmp(std::deque<vic> a, std::deque<vic> b) {
        for (int i = 0; i < std::min(a.size(), b.size()); i++) {
            if (a[i] < b[i]) {
                return true;
            }
        }
        return a.size() < b.size();
    }

    void mian() {
        for (int i = 1; i < n; i++) a[x[i]][y[i]] = true;
        for (int i = 1; i < n; i++) a[y[i]][x[i]] = true;
        vic S;
        S.clear();
        for (int i = 1; i <= s[0]; i++) S.push_back(s[i]);
        std::sort(S.begin(), S.end());
        vic t;
        t.clear();
        DFS(0, t);
        std::sort(SS.begin(), SS.end());
        /*
        for (auto i : SS) {
            for (auto j : i) {
                std::cout << j << ' ';
            }
            std::cout << '\n';
        }
        */
        while (SS.size() && SS.front() < S) SS.pop_front();
        if (SS.size() > k) {
            for (auto i : SS[k]) {
                std::cout << i << ' ';
            }
            std::cout << '\n';
        }
        return;
    }
}

int main() {
    freopen("mis.in", "r", stdin);
    freopen("mis.out", "w", stdout);
    std::cin >> n;
    std::cin >> k;
    for (int i = 1; i < n; i++) std::cin >> x[i];
    for (int i = 1; i < n; i++) std::cin >> y[i];
    std::cin >> s[0];
    for (int i = 1; i <= s[0]; i++) std::cin >> s[i];
    if (S1::is()) S1::mian();
}
#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2e5;

int t;
int n;
char s[maxN + 10];

int solve(int l, int r, char c) {
    if (l == r) return s[l] != c;
    int mid = (l + r) / 2;
    int les = solve(l, mid, c + 1);
    int res = solve(mid + 1, r, c + 1);
    for (int i = l; i <= mid; i++) if (s[i] != c) res++;
    for (int i = mid + 1; i <= r; i++) if (s[i] != c) les++;
    return std::min(les, res);
}

void mian() {
    std::cin >> n;
    std::cin >> (s + 1);
    std::cout << solve(1, n, 'a') << '\n';
    return;
}

int main() {
    promote();
    std::cin >> t;
    while (t--) mian();
    return 0;
}
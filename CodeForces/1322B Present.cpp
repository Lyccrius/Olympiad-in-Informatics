#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 4e5;
const int maxA = 1e7;
const int logA = 24;

int n;
int a[maxN + 10];
int b[maxN + 10];
int ans;

int calc(int s, int t) {
    if (s > t) return 0;
    int ret = 0;
    int l = 1;
    int r = 1;
    for (int i = n; i >= 1; i--) {
        while (l <= n && b[i] + b[l] < s) l++;
        while (r <= n && b[i] + b[r] <= t) r++;
        ret += r - l;
        if (l <= i && i < r) ret--;
    }
    return ret / 2;
}

bool solve(int p) {
    for (int i = 1; i <= n; i++) b[i] = a[i] & ((1 << (p + 1)) - 1);
    std::sort(b + 1, b + n + 1);
    return (calc(1 << p, (1 << (p + 1)) - 1) ^ calc((1 << (p + 1)) + (1 << p), (1 << (p + 2)) - 1)) & 1;
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 0; i <= logA; i++) ans |= solve(i) << i;
    std::cout << ans;
    return 0;
}
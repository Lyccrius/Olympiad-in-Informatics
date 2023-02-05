#include <iostream>

const int maxN = 2000;

int t;

int n;
int s[maxN + 10];

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) scanf("%1d", &s[i]);
    int l = 1;
    int r = n;
    while (l < r) {
        if (s[l] == s[r]) break;
        l++;
        r--;
    }
    std::cout << r - l + 1 << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
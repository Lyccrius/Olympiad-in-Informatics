#include <iostream>

typedef char chr;

const int maxN = 2e5;
const int maxQ = 2e5;

int n, q;
chr s[maxN + 10];
int l, r;
int next[maxN + 10];

int solve(chr *str, int n) {
    int ret = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        //printf("%c ", str[i]);
        while (j && str[i] != str[j + 1]) j = next[j];
        if (str[i] == str[j + 1]) j++;
        next[i] = j;
        //printf("next[%d] = %d\n", i, j);
        ret = std::max(ret, next[i]);
    }
    return ret;
}

int main() {
    freopen("border.in", "r", stdin);
    freopen("border.out", "w", stdout);
    std::cin >> n >> q;
    std::cin >> (s + 1);
    for (int i = 1; i <= q; i++) {
        std::cin >> l >> r;
        std::cout << solve(s + l, r - l + 1) << '\n';
    }
    return 0;
}
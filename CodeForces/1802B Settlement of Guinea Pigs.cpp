#include <iostream>
#include <algorithm>

const int maxN = 1e5;

int t;
int n;
int b[maxN + 10];

void mian() {
    int cnt = 0;
    int tot = 0;
    int ans = 0;
    int res = 0;
    int odd = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) {
        if (b[i] == 1) {
            cnt++;
            ans = std::max(ans, res + cnt);
            //printf("b[%d] = %d: cnt = %d, ans = %d\n", i, 1, cnt, ans);
        } else {
            tot += cnt;
            if (tot == 0) continue;
            if (tot & 1) {
                res = (tot + 1) / 2;
            } else {
                res = (tot - 2) / 2 + 2;
            }
            ans = std::max(ans, res);
            cnt = 0;
            //printf("b[%d] = %d: res = %d, ans = %d\n", i, 2, res, ans);
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
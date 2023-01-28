#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int t;
int n;
int a[maxN + 10];

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    a[n + 1] = 0;
    int cnt = 0;
    int last = 0;
    int lact = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        //printf("a[%d] = %d\n", i, a[i]);
        cnt++;
        if (a[i] == a[i + 1]) continue;
        if (a[i] == last + 1) {
            if (cnt > lact) {
                ans += cnt - lact;
            }
        } else {
            ans += cnt;
        }
        lact = cnt;
        last = a[i];
        cnt = 0;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
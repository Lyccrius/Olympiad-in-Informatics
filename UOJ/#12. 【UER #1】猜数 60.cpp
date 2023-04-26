#include <iostream>
#include <cmath>

typedef long long lxl;

int T;
lxl g, l;
int ans1, ans2;

void mian() {
    std::cin >> g >> l;
    lxl t = l / g;
    for (lxl i = sqrt(t); i; i--) {
        if (t % i == 0) {
            ans1 = (i + t / i) * g;
            //printf("t = %d, i = %d\n", t, i);
            break;
        }
    }
    ans2 = g + l;
    std::cout << ans1 << ' ' << ans2 << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}
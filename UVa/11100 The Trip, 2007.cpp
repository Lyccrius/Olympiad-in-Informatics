#include <iostream>
#include <algorithm>
#include <map>

typedef std::map<int, int> mii;

const int maxN = 10000;

int n;
int a[maxN + 10];
mii cnt;
int tot;
int fir = true;

void mian() {
    if (!fir) std::cout << '\n';
    fir = false;
    cnt.clear();
    tot = 0;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) cnt[a[i]]++;
    for (int i = 1; i <= n; i++) tot = std::max(tot, cnt[a[i]]);
    std::cout << tot << '\n';
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= tot; i++) {
        for (int j = i; j <= n; j += tot) {
            if (j != i) std::cout << ' ';
            std::cout << a[j];
        }
        std::cout << '\n';
    }
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}
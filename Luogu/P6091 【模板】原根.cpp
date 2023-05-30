#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 1e6;
const int maxD = 200;

int t;
int n, d;
int vis[maxN + 10];
int phi[maxN + 10];
vic prime;
int can[maxN + 10];
vic fac;
vic ans;

void init() {
    phi[1] = 1;
    for (int i = 2; i <= maxN; i++) {
        if (!vis[i]) {
            phi[i] = i - 1;
            prime.push_back(i);
        }
        for (auto j : prime) {
            if (i * j > maxN) break;
            vis[i * j] = true;
            if (i % j == 0) {
                phi[i * j] = phi[i] * j;
                break;
            }
            phi[i * j] = phi[i] * (j - 1);
        }
    }
    can[2] = true;
    can[4] = true;
    for (auto i : prime) {
        if (i == 2) continue;
        for (lxl j = i; j <= maxN; j *= i) can[j] = true;
        for (lxl j = 2 * i; j <= maxN; j *= i) can[j] = true;
    }
    return;
}

void div(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i) continue;
        fac.push_back(i);
        while (x % i == 0) x /= i;
    }
    if (x > 1) fac.push_back(x);
    return;
}

int pow(int a, int b, int p) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % p;
        a = 1ll * a * a % p;
        b = b / 2;
    }
    return ret;
}

bool check(int x) {
    for (auto i : fac) if (pow(x, phi[n] / i, n) == 1) return false;
    return true;
}

int get() {
    for (int i = 1; i <= n; i++) {
        if (pow(i, phi[n], n) != 1) continue;
        if (check(i)) return i;
    }
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void mian() {
    std::cin >> n >> d;
    fac.clear();
    ans.clear();
    if (can[n]) {
        div(phi[n]);
        lxl gen = get();
        lxl mul = 1;
        for (int i = 1; i <= phi[n]; i++) {
            mul = 1ll * mul * gen % n;
            if (gcd(i, phi[n]) == 1) ans.push_back(mul);
        }
        std::sort(ans.begin(), ans.end());
    }
    std::cout << ans.size() << '\n';
    for (int i = d; i <= ans.size(); i += d) std::cout << ans[i - 1] << ' ';
    std::cout << '\n';
    return;
}

int main() {
    init();
    std::cin >> t;
    while (t--) mian();
    return 0;
}
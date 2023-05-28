#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long lxl;
typedef std::vector<lxl> vlc;
typedef std::map<lxl, lxl> mll;

const lxl maxN = 1e12;
const lxl sqrN = 1e6;
const lxl maxM = 6720;
const lxl mod = 998244353;

lxl t;
lxl n;
vlc fac;
mll pos;
lxl f[maxM + 10][maxM + 10];

void mian() {
    fac.clear();
    pos.clear();
    std::fill(f[0], f[0] + sizeof(f[0]) / 8, 0);
    f[0][0] = 1;
    std::cin >> n;
    for (lxl i = 1; i * i <= n; i++) {
        if (n % i) continue;
        fac.push_back(i);
        if (i * i == n) continue;
        fac.push_back(n / i);
    }
    std::sort(fac.begin(), fac.end());
    for (int i = 0; i < fac.size(); i++) pos[fac[i]] = i;
    for (int i = 0; i < fac.size(); i++) {
        for (int j = 1; j < fac.size(); j++) {
            f[i][j] = f[i][j - 1];
            if (j > i) continue;
            if (fac[i] % fac[j]) continue;
            f[i][j] = (f[i][j] + f[pos[fac[i] / fac[j]]][j - 1]) % mod;
        }
    }
    std::cout << f[fac.size() - 1][fac.size() - 1] - 1 << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
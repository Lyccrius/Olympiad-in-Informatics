#include <iostream>
#include <vector>

typedef long long lxl;
typedef std::vector<lxl> vlc;

int t;
lxl n;
lxl prime[30] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

lxl mul(lxl a, lxl b, lxl mod) {
    lxl ret = 0;
    while (b) {
        if (b & 1) ret = (ret + a) % mod;
        a = a * 2 % mod;
        b = b / 2;
    }
    return ret;
}

lxl pow(lxl a, lxl b, lxl mod) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = mul(ret, a, mod);
        a = mul(a, a, mod);
        b = b / 2;
    }
    return ret;
}

bool MillerRabin(lxl n, lxl a) {
    lxl m = n - 1;
    lxl q = 0;
    while (m % 2 == 0) m /= 2, q++;
    lxl k = pow(a, m, n);
    if (k == 1) return true;
    for (lxl i = 0; i < q; i++) {
        if (k == n - 1) return true;
        k = mul(k, k, n);
    }
    return false;
}

bool isprime(lxl n) {
    if (n <= 1) return false;
    for (int i = 0; i < 24; i++) {
        if (n == prime[i]) return true;
        if (n % prime[i] == 0) return false;
        if (MillerRabin(n, prime[i]) == false) return false;
    }
    return true;
}

void mian() {
    std::cin >> n;
    if (isprime(n)) {
        std::cout << "YES" << '\n';
    } else {
        std::cout << "NO" << '\n';
    }
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
#include <iostream>
#include <algorithm>

typedef long long lxl;
typedef char chr;

const lxl mod = 19940417;
const lxl inv2 = 9970209;
const lxl inv6 = 3323403;

lxl read() {
    lxl ret = 0;
    lxl f = 1;
	chr ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = - 1;
		ch = getchar();
	}
	while (isdigit(ch))	{
        ret = (ret << 1) + (ret << 3) + (ch - '0');
        ch = getchar();
    }
	return f * ret;
}

lxl n, m;

lxl presum(lxl n) {
    return n * (n + 1) % mod * inv2 % mod;
}

lxl sum(lxl l, lxl r) {
    return ((presum(r) - presum(l - 1)) % mod + mod) % mod;
}

lxl prepow(lxl n) {
    return (n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod + mod) % mod;
}

lxl pow(lxl l, lxl r) {
    return ((prepow(r) - prepow(l - 1)) % mod + mod) % mod;
}

lxl f(lxl n) {
    lxl ret = n * n % mod;
    for (lxl i = 1, j, t; i <= n; i = j + 1) {
        t = n / i;
        j = n / t;
        ret = ((ret - t * sum(i, j) % mod) % mod + mod) % mod;
    }
    return ret;
}

lxl g(lxl n, lxl m) {
    lxl ret = n * n % mod * m % mod;
    for (lxl i = 1, j, t; i <= n; i = j + 1) {
        t = m / i;
        j = m / t;
        j = std::min(j, n);
        ret = ((ret - t * n % mod * sum(i, j) % mod) % mod + mod) % mod;
    }
    for (lxl i = 1, j, t; i <= n; i = j + 1) {
        t = n / i;
        j = n / t;
        j = std::min(j, n);
        ret = ((ret - t * m % mod * sum(i, j) % mod) + mod) % mod;
    }
    for (lxl i = 1, j, tn, tm; i <= n; i = j + 1) {
        tn = n / i;
        tm = m / i;
        j = std::min(n / tn, m / tm);
        j = std::min(n, j);
        ret = ((ret + tn * tm % mod * pow(i, j) % mod) % mod + mod) % mod;
    }
    return ret;
}

int main() {
    std::cin >> n >> m; if (n > m) std::swap(n, m);
    std::cout << ((f(n) * f(m) % mod - g(n, m)) % mod + mod) % mod;
    return 0;
}
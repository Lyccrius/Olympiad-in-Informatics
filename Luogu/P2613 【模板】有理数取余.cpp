#include <iostream>

typedef long long lxl;

const lxl mod = 19260817;

lxl a;
lxl b;

lxl read() {
    lxl ret = 0;
    lxl f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = - f;
        ch = getchar();
    }
    while (isdigit(ch)) {
        ret = ret * 10 + ch - '0';
        ret = ret % mod;
        ch = getchar();
    }
    return ret * f;
}

lxl pow(lxl a, lxl b) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b = b / 2;
    }
    return ret;
}

lxl inv(lxl a) {
    return pow(a, mod - 2);
}

int main() {
    a = read();
    b = read();
    if (b == 0) {
        std::cout << "Angry!";
    } else {
        std::cout << a * inv(b) % mod;
    }
    return 0;
}
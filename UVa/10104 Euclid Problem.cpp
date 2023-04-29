#include <iostream>

int A, B;
int x, y, D;

int exgcd(int a, int &x, int b, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int ret = exgcd(b, y, a % b, x);
    y -= a / b * x;
    return ret;
}

void mian() {
    D = exgcd(A, x, B, y);
    std::cout << x << ' ' << y << ' ' << D << '\n';
    return;
}

int main() {
    while (std::cin >> A >> B) mian();
    return 0;
}
#include <iostream>

const int sqrN = 31622;
const int logN = 30;

int n, m;
int a, b;
int v[sqrN + 10][logN + 10];
int f[sqrN + 10][logN + 10];

int pow(int a, int b) {
    int ret = 1;
    for (int i = 1; i <= b; i++) {
        if (ret > n / a) return n + 1;
        ret *= a;
    }
    return ret;
}

bool check(int a, int b) {
    if (pow(a, b) > n) return true;
    if (b == 1 && a > n / a) return (n - a) % 2;
    if (v[a][b]) return f[a][b];
    v[a][b] = true;
    f[a][b] = (!check(a + 1, b)) || (!check(a, b + 1));
    return f[a][b];
}

void mian() {
    std::cin >> a >> b;
    if (check(a, b)) std::cout << "Yes" << '\n';
    else std::cout << "No" << '\n';
    return;
}

int main() {
    std::cin >> n >> m;
    while (m--) mian();
    return 0;
}
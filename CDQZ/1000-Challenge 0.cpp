#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int a[maxN + 10];
char op; int x, y;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 'M') {
            std::cin >> x >> y;
            a[x] = y;
        } else if (op == 'Q') {
            std::cin >> x;
            std::cout << a[x] << '\n';
        }
    }
    return 0;
}
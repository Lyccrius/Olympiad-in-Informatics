#include <iostream>

int N;
int ans = 1e6;

int calc(int x) {
    int ret = 0;
    while (x) {
        ret += x % 10;
        x /= 10;
    }
    return ret;
}

int main() {
    std::cin >> N;
    for (int a = 1; a <= N; a++) {
        int b = N - a;
        if (a > b) break;
        ans = std::min(ans, calc(a) + calc(b));
    }
    std::cout << ans << '\n';
    return 0;
}
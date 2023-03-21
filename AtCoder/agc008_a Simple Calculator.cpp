#include <iostream>
#include <cmath>

int x, y;
int X, Y;
int ans;

int main() {
    std::cin >> x >> y;
    X = std::abs(x);
    Y = std::abs(y);
    if (X > Y) {
        if (x > 0) ans++;
        ans += (X - Y);
        if (y > 0) ans++;
        std::cout << ans;
    } else if (X < Y) {
        if (x < 0) ans++;
        ans += (Y - X);
        if (y < 0) ans++;
        std::cout << ans;
    } else {
        std::cout << (x != y);
    }
    return 0;
}
#include <iostream>
#include <algorithm>

int A, B, C;
int tot;
int ans;

int main() {
    std::cin >> A >> B >> C;
    tot = std::min(A + B, C);
    ans += std::min(C, tot + 1);
    ans += B;
    std::cout << ans;
    return 0;
}
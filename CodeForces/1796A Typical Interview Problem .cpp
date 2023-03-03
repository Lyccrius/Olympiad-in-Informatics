#include <iostream>
#include <vector>

const int maxK = 10;

char fb[50] = "FBFFBFFBFBFFBFFBFBFFBFFBFBFFBFFB";

int t;
int k;
char s[maxK + 10];

void mian() {
    std::cin >> k;
    for (int i = 1; i <= k; i++) std::cin >> s[i];
    for (int i = 0; i <= 15; i++) {
        for (int j = 1; j <= k; j++) {
            if (fb[i + j - 1] != s[j]) {
                break;
            }
            if (j == k) {
                std::cout << "YES" << '\n';
                return;
            }
        }
    }
    std::cout << "NO" << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
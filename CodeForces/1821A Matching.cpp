#include <iostream>
#include <cstring>

typedef char chr;

const int maxN = 5;

int t;
chr s[maxN + 10];
int n;

void mian() {
    std::cin >> (s + 1);
    n = strlen(s + 1);
    if(s[1] == '0') {
        std::cout << '0' << '\n';
        return;
    }
    int ans = 1;
    bool flag = true;
    if (s[1] == '?') ans = 9;
    for (int i = 2; i <= n; i++) {
        if (s[i] == '?') {
            ans *= 10;
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
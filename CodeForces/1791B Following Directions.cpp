#include <iostream>

const int maxN = 50;

int t;

int n;
char s[maxN + 10];

void mian() {
    std::cin >> n;
    std::cin >> (s + 1);
    int x = 0;
    int y = 0;
    bool ok = false;
    for (int i = 1; i <= n; i++) {
        switch (s[i]) {
            case 'L': {
                x--;
                break;
            }
            case 'R': {
                x++;
                break;
            }
            case 'U': {
                y++;
                break;
            }
            case 'D': {
                y--;
                break;
            }
        }
        if (x == 1 && y == 1) ok = true;
    }
    if (ok) std::cout << "YES\n";
    else std::cout << "NO\n";
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
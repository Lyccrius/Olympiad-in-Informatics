#include <iostream>

typedef char chr;

int t;
int n;
int c[30];
int v[30];
chr s[30];

void mian() {
    std::cin >> (s + 1);
    for (int i = 1; i <= 26; i++) c[i] = 0;
    for (int i = 1; i <= 26; i++) v[i] = 0;
    for (int i = 1, j; i <= 26; i++) {
        n = 0;
        j = i;
        while (!v[j]) {
            v[j] = true;
            j = s[j] - 'A' + 1;
            n++;
        }
        c[n]++;
    }
    for (int i = 2; i <= 26; i += 2) {
        if (c[i] & 1) {
            std::cout << "No" << '\n';
            return;
        }
    }
    std::cout << "Yes" << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}
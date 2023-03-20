#include <iostream>
#include <string>

typedef std::string str;

const str atcoder = "atcoder";

int T;
str S;

void mian() {
    std::cin >> S;
    if (atcoder < S) {
        std::cout << 0 << '\n';
        return;
    }
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'a') continue;
        if (S[i] > 't') {
            std::cout << i - 1 << '\n';
        } else {
            std::cout << i << '\n';
        }
        return;
    }
    std::cout << - 1 << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}
#include <iostream>
#include <string>

std::string S;

bool n, w, s, e;

int main() {
    std::cin >> S;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'N') n = true;
        if (S[i] == 'W') w = true;
        if (S[i] == 'S') s = true;
        if (S[i] == 'E') e = true;
    }
    if ((n ^ s) || (w ^ e)) {
        std::cout << "No";
    } else {
        std::cout << "Yes";
    }
    return 0;
}
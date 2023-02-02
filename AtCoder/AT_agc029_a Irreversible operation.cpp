#include <iostream>
#include <string>

typedef long long lxl;

std::string S;
lxl cnt;
lxl ans;

int main() {
    std::cin >> S;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'B') cnt++;
        else ans += cnt;
    }
    std::cout << ans;
    return 0;
}
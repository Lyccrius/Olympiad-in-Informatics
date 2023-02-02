#include <iostream>
#include <string>

typedef long long lxl;

std::string S;

lxl cnt;
lxl ans;

int main() {
    std::cin >> S;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'A') cnt++;
        else if (S[i] == 'B' && S[i + 1] == 'C') ans += cnt, i++;
        else cnt = 0;
    }
    std::cout << ans;
    return 0;
}
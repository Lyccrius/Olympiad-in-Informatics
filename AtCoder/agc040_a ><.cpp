#include <iostream>
#include <algorithm>
#include <string>

typedef long long lxl;

const int maxN = 5e5;

std::string S;

int num[maxN + 10];
lxl sum;

int main() {
    std::cin >> S;
    for (int i = 0; i < S.size(); i++) if (S[i] == '<') num[i + 1] = num[i] + 1;
    for (int i = S.size() - 1; i >= 0; i--) if (S[i] == '>') num[i] = std::max(num[i], num[i + 1] + 1);
    for (int i = 0; i <= S.size(); i++) sum += num[i];
    std::cout << sum;
    return 0;
}
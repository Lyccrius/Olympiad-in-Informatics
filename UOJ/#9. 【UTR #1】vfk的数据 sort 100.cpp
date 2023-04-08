#include <iostream>
#include <algorithm>
#include <string>

typedef std::string str;

const int maxN = 10000;
const int maxM = 100;

int n;
str s[maxN + 10];

bool cmp(const str &a, const str &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> s[i];
    std::sort(s + 1, s + n + 1, cmp);
    for (int i = 1; i <= n; i++) std::cout << s[i] << '\n';
    return 0;
}
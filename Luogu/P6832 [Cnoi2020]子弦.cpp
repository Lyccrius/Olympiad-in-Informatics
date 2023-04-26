#include <iostream>
#include <algorithm>
#include <map>

typedef char chr;
typedef std::map<chr, int> mci;

const int maxN = 1e7;

chr S[maxN + 10];
mci c;
int p;

int main() {
    std::cin >> (S + 1);
    for (int i = 1; S[i]; i++) c[S[i]]++, p = std::max(p, c[S[i]]);
    std::cout << p << '\n';
    return 0;
}
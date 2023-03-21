#include <iostream>
#include <cstring>

typedef long long lxl;

const int maxN = 1e5;

int N;
char S[maxN + 10];
lxl ans;

int main() {
    std::cin >> (S + 1);
    N = std::strlen(S + 1);
    for (int i = 1; i <= N; i++) {
        if (S[i] == 'U') {
            ans += (N - i);
            ans += (i - 1) * 2;
        } else {
            ans += (i - 1);
            ans += (N - i) * 2;
        }
    }
    std::cout << ans;
    return 0;
}
#include <iostream>
#include <cstring>

const int maxN = 100;

int N;
char S[maxN + 10];
int last[30];
int res[30];
int ans;

int main() {
    std::cin >> (S + 1);
    N = std::strlen(S + 1);
    for (int i = 1; i <= N; i++) {
        int ch = S[i] - 'a';
        res[ch] = std::max(res[ch], i - last[ch] - 1);
        last[ch] = i;
    }
    ans = N;
    for (int ch = 0; ch <= 25; ch++) ans = std::min(ans, std::max(res[ch], N - last[ch]));
    std::cout << ans;
    return 0;
}
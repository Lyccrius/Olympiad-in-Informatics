#include <iostream>
#include <cstring>

typedef char chr;

const int maxN = 26;

chr S[maxN + 10];
int N;
int C[maxN + 10];
int D;

int main() {
    std::cin >> (S + 1);
    N = std::strlen(S + 1);
    for (int i = 1; i <= N; i++) {
        if (C[S[i] - 'a' + 1] == 0) D++;
        C[S[i] - 'a' + 1]++;
    }
    if (N < 26) {
        std::cout << (S + 1);
        for (int i = 1; i <= 26; i++) {
            if (C[i] == 0) {
                std::cout << (chr) ('a' + i - 1);
                break;
            }
        }
    } else {
        bool flag = false;
        int suf = 0;
        for (int i = N; i >= 1; i--) {
            if (suf > S[i] - 'a' + 1) {
                for (int j = N; j > i; j--) {
                    if (S[j] < S[i]) continue;
                    suf = std::min(suf, S[j] - 'a' + 1);
                }
                for (int j = 1; j < i; j++) std::cout << S[j];
                std::cout << (chr) ('a' + suf - 1);
                flag = true;
                break;
            }
            suf = std::max(suf, S[i] - 'a' + 1);
        }
        if (!flag) {
            std::cout << -1;
        }
    }
    return 0;
}
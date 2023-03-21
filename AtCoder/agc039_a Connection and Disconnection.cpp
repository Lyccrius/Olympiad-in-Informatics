#include <iostream>
#include <string>

typedef long long lxl;

std::string S;
lxl K;

bool allsame() {
    for (int i = 1; i < S.size(); i++) {
        if (S[i] != S[i - 1]) return false;
    }
    return true;
}

int main() {
    std::cin >> S >> K;
    lxl N = S.size();
    std::string T = S + S;
    lxl M = T.size();
    lxl ansS = 0;
    lxl ansT = 0;
    if (allsame()) {
        std::cout << N * K / 2;
        return 0;
    }
    for (int i = 0; i < N; i++) if (S[i] == S[i + 1]) ansS++, i++;
    for (int i = 0; i < M; i++) if (T[i] == T[i + 1]) ansT++, i++;
    ansT -= ansS;
    std::cout << ansS + ansT * (K - 1);
    return 0;
}
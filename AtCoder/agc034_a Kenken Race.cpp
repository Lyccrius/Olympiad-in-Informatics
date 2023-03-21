#include <iostream>

const int maxN = 2e5;

int N, A, B, C, D;
char S[maxN + 10];

int main() {
    std::cin >> N >> A >> B >> C >> D;
    std::cin >> (S + 1);
    //S[0] = '#';
    //S[N + 1] = '#';
    bool ok = true;
    if (C == D) ok = false;
    if (S[C] == '#' || S[D] == '#') ok = false;
    //if (C < D) {
        for (int i = A; i <= C; i++) if (S[i] == '#' && S[i + 1] == '#') ok = false;
        for (int i = B; i <= D; i++) if (S[i] == '#' && S[i + 1] == '#') ok = false;
    //}
    if (C > D) {
        bool solve = false;
        for (int i = B; i <= D; i++) if (S[i - 1] == '.' && S[i] == '.' && S[i + 1] == '.') solve = true;
        if (!solve) ok = false;
    }
    if (ok) std::cout << "Yes";
    else std::cout << "No";
    return 0;
}
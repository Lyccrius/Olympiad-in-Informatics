#include <iostream>

const int maxN = 100;

int N;
char s[maxN + 10], t[maxN + 10];

int main() {
    std::cin >> N;
    std::cin >> (s + 1);
    std::cin >> (t + 1);
    int i, j;
    for (i = 1, j = 1; i <= N; i++) if (s[i] == t[j]) j++;
    std::cout << N * 2 - j + 1;
    return 0;
}
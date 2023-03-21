#include <iostream>

const int maxN = 1e5;
const int maxA = 1e5;

int N;
int A[maxN + 10];
int C[maxA + 10];
int cnt;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        std::cin >> A[i];
        if (C[A[i]]) cnt++;
        C[A[i]]++;
    }
    if (cnt & 1) cnt++;
    std::cout << N - cnt;
    return 0;
}
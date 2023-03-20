#include <iostream>

typedef long long lxl;

const int maxN = 1e5;

int N;
int A[maxN + 10];
lxl sum;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) sum += A[i];
    if (sum & 1) {
        std::cout << "NO" << '\n';
    } else {
        std::cout << "YES" << '\n';
    }
    return 0;
}
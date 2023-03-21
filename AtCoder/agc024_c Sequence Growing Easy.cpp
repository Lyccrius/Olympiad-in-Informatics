#include <iostream>

typedef long long lxl;

const int maxN = 2e5;

int N;
int A[maxN + 10];
lxl ans;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    if (A[1] != 0) {
        std::cout << - 1 << '\n';
        return 0;
    }
    for (int i = 2; i <= N; i++) {
        if (A[i] > A[i - 1] + 1) {
            std::cout << - 1 << '\n';
            return 0;
        }
    }
    for (int i = 2; i <= N; i++) {
        if (A[i] == A[i - 1] + 1) {
            ans += 1;
        } else {
            ans += A[i];
        }
    }
    std::cout << ans << '\n';
    return 0;
}
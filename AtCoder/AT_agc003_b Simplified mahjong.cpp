#include <iostream>

typedef long long lxl;

const lxl maxN = 1e5;

lxl N;
lxl A[maxN + 10];
lxl ans;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) {
        ans += A[i] / 2;
        A[i] %= 2;
        if (A[i] && A[i + 1]) {
            A[i]--;
            A[i + 1]--;
            ans += 1;
        }
    }
    std::cout << ans;
    return 0;
}
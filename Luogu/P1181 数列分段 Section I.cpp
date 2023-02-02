#include <iostream>

typedef long long lxl;

const int maxN = 1e5;

lxl N, M;
lxl A[maxN + 10];
lxl sum;
lxl cnt;

int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) {
        sum += A[i];
        if (sum > M) {
            sum = A[i];
            cnt++;
        }
    }
    std::cout << cnt + 1;
    return 0;
}
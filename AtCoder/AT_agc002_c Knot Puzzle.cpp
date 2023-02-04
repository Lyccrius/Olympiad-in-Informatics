#include <iostream>

const int maxN = 1e5;

int N, L;
int A[maxN + 10];
int cur;

int main() {
    std::cin >> N >> L;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) if (A[i] + A[i + 1] > A[cur] + A[cur + 1]) cur = i;
    if (A[cur] + A[cur + 1] >= L) {
        std::cout << "Possible\n";
        for (int i = N - 1; i > cur; i--) std::cout << i << '\n';
        for (int i = 1; i <= cur; i++) std::cout << i << '\n';
    } else {
        std::cout << "Impossible\n";
    }
    return 0;
}
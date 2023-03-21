#include <iostream>

typedef long long lxl;

const int maxN = 1e5 + 10;

int N;
int A[maxN + 10];
lxl ans;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) {
        if (A[i - 1] && A[i]) {
            A[i]--;
            ans++;
        }
        ans += A[i] / 2;
        A[i] %= 2;
    }
    std::cout << ans << '\n';
    return 0;
}
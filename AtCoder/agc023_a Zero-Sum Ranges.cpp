#include <iostream>
#include <map>

typedef long long lxl;
typedef std::map<lxl, int> mli;

const int maxN = 2e5;

int N;
int A[maxN + 10];
lxl B[maxN + 10];
mli C;
lxl ans;

int main() {
    C[0] = 1;
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) B[i] = B[i - 1] + A[i];
    for (int i = 1; i <= N; i++) ans += C[B[i]], C[B[i]]++;
    std::cout << ans;
    return 0;
}
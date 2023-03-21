#include <iostream>
#include <algorithm>
#include <map>

typedef std::map<int, int> mii;

const int maxN = 1e5;

int N;
int A[maxN + 10];
mii B;
int C;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= N; i++) B[A[i]] = i;
    std::sort(A + 1, A + N + 1);
    for (int i = 1; i <= N; i++) if ((B[A[i]] - i) & 1) C++;
    std::cout << C / 2;
    return 0;
}
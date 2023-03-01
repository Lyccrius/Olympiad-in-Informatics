#include <iostream>
#include <map>

typedef std::map<int, int> mii;

const int maxN = 4000;

int T;
int n;
int A[maxN + 10], B[maxN + 10], C[maxN + 10], D[maxN + 10];

void mian() {
    mii cnt;
    int ans = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> A[i] >> B[i] >> C[i] >> D[i];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cnt[A[i] + B[j]]++;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) ans += cnt[- C[i] - D[j]];
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}
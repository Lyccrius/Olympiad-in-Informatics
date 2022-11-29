#include <cstdio>
#include <cstring>
#include <deque>

const int maxN = 2e5 + 10;
const int inf = 1e9 + 10;

int N, L, R;
int A[maxN];
int F[maxN];
std::deque<int> icy;
int ans = -inf;

int main() {
    std::memset(F, 0x80, sizeof(F));
    F[0] = A[0];
    scanf("%d%d%d", &N, &L, &R);
    for (int i = 1; i <= N + 1; i++) scanf("%d", &A[i - 1]);
    for (int i = L; i <= N; i++) {
        while (!icy.empty() && icy.front() < i - R) icy.pop_front();
        while (!icy.empty() && F[icy.back()] < F[i - L]) icy.pop_back();
        icy.push_back(i - L);
        F[i] = F[icy.front()] + A[i];
        if (i + R > N) ans = std::max(ans, F[i]);
    }
    printf("%d\n", ans);
    return 0;
}
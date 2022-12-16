#include <cstdio>
#include <algorithm>

const int maxN = 1e6 + 10;

int n;

struct Node {
    int a, b;

    bool operator<(Node other) const {
        return b < other.b;
    }
} contest[maxN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &contest[i].a, &contest[i].b);
    std::sort(contest + 1, contest + n + 1);
    int last = -1;
    int res = 0;
    for (int i = 1; i <= n; i++) if (last <= contest[i].a) res++, last = contest[i].b;
    printf("%d\n", res);
    return 0;
}
#include <cstdio>
#include <algorithm>

const int maxN = 2e6 + 10;
const int maxM = 5000 + 10;

int n, m;
struct Node {
    int p;
    int a;
    bool operator<(Node other) const {
        return p < other.p;
    }
} farmer[maxM];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d", &farmer[i].p, &farmer[i].a);
    std::sort(farmer + 1, farmer + m + 1);
    int cur = 1;
    int sum = 0;
    while (n > 0) {
        if (!farmer[cur].a) cur++;
        sum += farmer[cur].p;
        farmer[cur].a--;
        n--;
    }
    printf("%d\n", sum);
    return 0;
}
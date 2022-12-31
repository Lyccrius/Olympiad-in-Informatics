#include <cstdio>
#include <queue>
#include <vector>

const int maxN = 100;
const int maxM = 100;

int t;

int n, m;
int a[maxN + 10];
int b[maxM + 10];
long long sum;

void mian() {
    scanf("%d%d", &n, &m);
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    while (q.size()) q.pop();
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), q.push(a[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &b[i]), q.pop(), q.push(b[i]);
    sum = 0;
    while (q.size()) {
        sum += q.top();
        q.pop();
    }
    printf("%lld\n", sum);
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}
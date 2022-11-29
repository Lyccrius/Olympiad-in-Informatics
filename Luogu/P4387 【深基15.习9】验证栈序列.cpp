#include <cstdio>
#include <stack>

const int maxN = 1e5 + 10;

int q;
int n;
int pushed[maxN];
int poped[maxN];

void mian() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &pushed[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &poped[i]);
    std::stack<int> sta;
    int cur = 1;
    for (int i = 1; i <= n; i++) {
        sta.push(pushed[i]);
        while (!sta.empty() && sta.top() == poped[cur]) sta.pop(), cur++;
    }
    if (cur == n + 1) printf("Yes\n");
    else printf("No\n");
    return;
}

int main() {
    scanf("%d", &q);
    while (q--) mian();
    return 0;
}
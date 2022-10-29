#include <cstdio>
#include <stack>

const int maxn = 3e6 + 10;

int n;
int a[maxn];
int f[maxn];

std::stack<int> monotonousStack;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        while (!monotonousStack.empty() && a[monotonousStack.top()] < a[i]) {
            f[monotonousStack.top()] = i;
            monotonousStack.pop();
        }
        monotonousStack.push(i);
    }

    for (int i = 1; i <= n; i++) printf("%d ", f[i]);

    return 0;
}
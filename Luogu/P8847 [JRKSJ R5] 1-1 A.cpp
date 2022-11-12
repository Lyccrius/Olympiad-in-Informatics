#include <cstdio>
#include <queue>

int n;
int a;

std::priority_queue<int> positive;
std::priority_queue<int> negative;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        if (a == 1) positive.push(-a);
        else negative.push(a);
    }
    if (positive.size() > negative.size()) {
        while (!positive.empty() && !negative.empty()) {
            printf("%d ", -positive.top());
            printf("%d ", negative.top());
            positive.pop();
            negative.pop();
        }
        while (!positive.empty()) {
            printf("%d ", -positive.top());
            positive.pop();
        }
    } else {
        while (!negative.empty() && !positive.empty()) {
            printf("%d ", negative.top());
            printf("%d ", -positive.top());
            negative.pop();
            positive.pop();
        }
        while (!negative.empty()) {
            printf("%d ", negative.top());
            negative.pop();
        }
    }
    return 0;
}
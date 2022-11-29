#include <cstdio>
#include <deque>

const int maxn = 2e6 + 10;

int n, k;
int a[maxn];

std::deque<int> dequeMin;
std::deque<int> ansMin;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    ansMin.push_back(0);
    for (int i = 1; i < n; i++) {
        while (!dequeMin.empty() && 
                dequeMin.front() <= i - k) 
                dequeMin.pop_front();
        while (!dequeMin.empty() && 
                a[dequeMin.back()] > a[i])
                dequeMin.pop_back();
        dequeMin.push_back(i);
        
        ansMin.push_back(dequeMin.front());
    }

    while (!ansMin.empty()) {
        printf("%d\n", a[ansMin.front()]);
        ansMin.pop_front();
    }

    return 0;
}
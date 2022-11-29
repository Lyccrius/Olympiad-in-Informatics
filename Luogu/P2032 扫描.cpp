#include <cstdio>
#include <deque>

const int maxn = 1e6 + 10;

int n, k;
int a[maxn];

std::deque<int> dequeMax;
std::deque<int> ansMax;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        
        while (!dequeMax.empty() && 
                dequeMax.front() <= i - k) 
                dequeMax.pop_front();
        while (!dequeMax.empty() && 
                a[dequeMax.back()] < a[i])
                dequeMax.pop_back();
        dequeMax.push_back(i);
        
        if (i >= k) 
            ansMax.push_back(dequeMax.front());
    }

    while (!ansMax.empty()) {
        printf("%d\n", a[ansMax.front()]);
        ansMax.pop_front();
    }

    return 0;
}
#include <cstdio>
#include <deque>

const int maxn = 1e6 + 10;

int n, k;
int a[maxn];

std::deque<int> dequeMin;
std::deque<int> dequeMax;
std::deque<int> ansMin;
std::deque<int> ansMax;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);

        while (!dequeMin.empty() && 
                dequeMin.front() <= i - k) 
                dequeMin.pop_front();
        while (!dequeMin.empty() && 
                a[dequeMin.back()] > a[i])
                dequeMin.pop_back();
        dequeMin.push_back(i);
        
        while (!dequeMax.empty() && 
                dequeMax.front() <= i - k) 
                dequeMax.pop_front();
        while (!dequeMax.empty() && 
                a[dequeMax.back()] < a[i])
                dequeMax.pop_back();
        dequeMax.push_back(i);
        
        if (i >= k) {
            ansMin.push_back(dequeMin.front());
            ansMax.push_back(dequeMax.front());
        }
    }

    while (!ansMin.empty()) {
        printf("%d ", a[ansMin.front()]);
        ansMin.pop_front();
    }
    printf("\n");
    while (!ansMax.empty()) {
        printf("%d ", a[ansMax.front()]);
        ansMax.pop_front();
    }

    return 0;
}
#include <cstdio>
#include <queue>

const int maxn = 1e5 + 10;

int N;
int A[maxn];
int B[maxn];

std::priority_queue<int, std::vector<int>, std::greater<int> > q;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= N; i++) scanf("%d", &B[i]);
    for (int i = 1; i <= N; i++) 
        for (int j = 1; (i - 1) * (j - 1) <= N && j <= N; j++)
            q.push(A[i] + B[j]);
    for (int i = 1; i <= N; i++) {
        printf("%d ", q.top());
        q.pop();
    }
    printf("\n");
    return 0;
}
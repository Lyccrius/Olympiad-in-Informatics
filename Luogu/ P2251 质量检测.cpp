#include <cstdio>
#include <deque>

const int maxN = 1e6 + 10;

int N, M;
int A[maxN];

std::deque<int> P;
std::deque<int> Q;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);

        while (!P.empty() && 
                P.front() <= i - M)
                P.pop_front();
        while (!P.empty() && 
                A[P.back()] > A[i])
                P.pop_back();
        P.push_back(i);
        
        if (i >= M) {
            Q.push_back(P.front());
        }
    }

    while (!Q.empty()) {
        printf("%d\n", A[Q.front()]);
        Q.pop_front();
    }

    return 0;
}
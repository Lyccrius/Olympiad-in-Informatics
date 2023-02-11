#include <iostream>
#include <deque>

const int maxN = 1e3;
const int maxL = 1e6;
const int maxA = 1e3;
const int inf = 1e9;

int N, L;
int A, B;
int S[maxN + 10], E[maxN + 10];
int D[maxL + 10];
int F[maxL + 10];
int P;
std::deque<int> Q;

int main() {
    std::cin >> N >> L;
    std::cin >> A >> B;
    A *= 2;
    B *= 2;
    for (int i = 1; i <= N; i++) std::cin >> S[i] >> E[i];
    for (int i = 1; i <= N; i++) D[S[i] + 1]++, D[E[i]]--;
    //for (int i = 1; i <= L; i++) printf("%d ", D[i]);
    //printf("\n");
    for (int i = 1; i <= L; i++) {
        P += D[i];
        if (i & 1) continue;
        while (!Q.empty() && Q.front() < i - B) {
            //printf("Q.pop_front(%d)\n", Q.front());
            Q.pop_front();
        }
        if (i >= A) {
            while (!Q.empty() && F[Q.back()] >= F[i - A]) {
                //printf("Q.pop_back(%d)\n", Q.back());
                Q.pop_back();
            }
            Q.push_back(i - A);
            //printf("Q.push_back(%d)\n", Q.back());
        }
        if (!Q.empty() && F[Q.front()] < inf && P == 0) F[i] = F[Q.front()] + 1;
        else F[i] = inf;
        //printf("F[%d] = %d\n", i, F[i]);
    }
    if (F[L] == inf) F[L] = -1;
    std::cout << F[L];
    return 0;
}
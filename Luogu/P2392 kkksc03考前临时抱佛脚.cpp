#include <cstdio>
#include <cstring>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxS = 20 + 10;

int s1, s2, s3, s4;
int A[maxS];
int B[maxS];
int C[maxS];
int D[maxS];
int sumA;
int sumB;
int sumC;
int sumD;

int DFS(int* problem, int visited[], int cur, int s, int res, int sum) {
    if (cur > s) {
        return std::max(res, sum - res);
    }
    int ans = inf;
    visited[cur] = true;
    ans = std::min(ans, DFS(problem, visited, cur + 1, s, res + problem[cur], sum));
    visited[cur] = false;
    ans = std::min(ans, DFS(problem, visited, cur + 1, s, res, sum));
    ans = std::max(ans, sum - ans);
    return ans;
}

int main() {
    scanf("%d%d%d%d", &s1, &s2, &s3, &s4);
    for (int i = 1; i <= s1; i++) { scanf("%d", &A[i]); sumA += A[i]; }
    for (int i = 1; i <= s2; i++) { scanf("%d", &B[i]); sumB += B[i]; }
    for (int i = 1; i <= s3; i++) { scanf("%d", &C[i]); sumC += C[i]; }
    for (int i = 1; i <= s4; i++) { scanf("%d", &D[i]); sumD += D[i]; }
    int vA[maxS];
    int vB[maxS];
    int vC[maxS];
    int vD[maxS];
    std::memset(vA, 0, sizeof(vA));
    std::memset(vB, 0, sizeof(vB));
    std::memset(vC, 0, sizeof(vC));
    std::memset(vD, 0, sizeof(vD));
    int ansA = DFS(A, vA, 1, s1, 0, sumA);
    int ansB = DFS(B, vB, 1, s2, 0, sumB);
    int ansC = DFS(C, vC, 1, s3, 0, sumC);
    int ansD = DFS(D, vD, 1, s4, 0, sumD);
    int ans = 0;
    ansA = std::max(ansA, sumA - ansA);
    ansB = std::max(ansB, sumB - ansB);
    ansC = std::max(ansC, sumC - ansC);
    ansD = std::max(ansD, sumD - ansD);
    ans += ansA;
    ans += ansB;
    ans += ansC;
    ans += ansD;
    printf("%d\n", ans);
    return 0;
}
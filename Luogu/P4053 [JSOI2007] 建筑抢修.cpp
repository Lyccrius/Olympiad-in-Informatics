#include <cstdio>
#include <algorithm>
#include <queue>

const int maxN = 1.5e5;

int N;
struct Node {
    long long T1, T2;

    bool operator<(const Node &other) const {
        return T2 < other.T2;
    }
} Building[maxN + 10];

std::priority_queue<long long> Heap;
long long T;
int S;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%lld%lld", &Building[i].T1, &Building[i].T2);
    std::sort(Building + 1, Building + N + 1);
    for (int i = 1; i <= N; i++) {
        T += Building[i].T1;
        Heap.push(Building[i].T1);
        if (T <= Building[i].T2) S++;
        else T -= Heap.top(), Heap.pop();
    }
    printf("%d\n", S);
    return 0;
}
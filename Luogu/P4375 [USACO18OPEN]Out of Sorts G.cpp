#include <cstdio>
#include <algorithm> 

const int maxN = 1e5;

int N;
struct Node {
    int val;
    int rank;
    bool operator <(const Node& other) const {
        if (val == other.val) return rank < other.rank;
        return val < other.val;
    }
} A[maxN + 10];

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN + 10];

    int LowBit(int val) {
        return val & -val;
    }

    void Add(int pos, int val) {
        while (pos <= N) {
            node[pos].val += val;
            pos += LowBit(pos);
        }
        return;
    }

    int Ask(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += node[pos].val;
            pos -= LowBit(pos);
        }
        return ret;
    }
} BIT;

int ans = 1;

int main() {
	scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i].val), A[i].rank = i;
    std::sort(A + 1, A + N + 1);
    for (int i = 1; i <= N; i++) {
        BIT.Add(A[i].rank, 1);
        ans = std::max(ans, i - BIT.Ask(i));
    }
   printf("%d\n", ans);
   return 0;
}
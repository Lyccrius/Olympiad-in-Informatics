#include <cstdio>
#include <stack>

const int maxN = 1e5;
const int maxQ = 2e5;
const int logN = 16;

const int inf = 1e9 + 10;
int log[maxN + 10];

int N, Q;
int D[maxN + 10], C[maxN + 10];
int R[maxQ + 10], V[maxQ + 10];

struct ST {
    int next[maxN + 10][logN + 10];
    int size[maxN + 10][logN + 10];

    void PreWork() {
        for (int i = 2; i <= N; i++) log[i] = log[i >> 1] + 1;
        for (int j = 1; j <= logN; j++) for (int i = 1; i <= N; i++) {
            next[i][j] = next[next[i][j - 1]][j - 1];
            size[i][j] = size[i][j - 1] + size[next[i][j - 1]][j - 1];
        }
        return;
    }
} st;

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) scanf("%d%d", &D[i], &C[i]);
    for (int i = 1; i <= Q; i++) scanf("%d%d", &R[i], &V[i]);
    std::stack<int> under;
    D[N + 1] = inf;
    C[N + 1] = inf;
    under.push(N + 1);
    for (int i = N; i >= 1; i--) {
        while (D[under.top()] <= D[i]) under.pop();
        st.next[i][0] = under.top();
        st.size[i][0] = C[under.top()];
        under.push(i);
    }
    st.PreWork();
    for (int i = 1; i <= Q; i++) {
        if (V[i] > C[R[i]]) {
            V[i] -= C[R[i]];
            for (int p = logN; p >= 0; p--) {
                if (V[i] > st.size[R[i]][p]) {
                    V[i] -= st.size[R[i]][p];
                    R[i] = st.next[R[i]][p];
                }
            }
            R[i] = st.next[R[i]][0];
        }
        R[i] %= N + 1;
        printf("%d\n", R[i]);
    }
    return 0;
}
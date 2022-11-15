#include <cstdio>
#include <map>

const int maxN = 24 + 10;

int N;
int A[maxN];
char s[10000 + 10];
std::map<int, int> table;

int bitCount(int x) {
    if (x == 0) return 0;
    return bitCount(x / 2) + (x & 1);
}

int main() {
    while (scanf("%d", &N) == 1 && N) {
        char s[1000 + 10];
        for (int i = 0; i < N; i++) {
            scanf("%s", s);
            A[i] = 0;
            for (int j = 0; s[j] != '\0'; j++) A[i] ^= (1 << (s[j] - 'A'));
        }
        table.clear();
        int N1 = N / 2;
        int N2 = N - N1;
        for (int i = 0; i < (1 << N1); i++) {
            int x = 0;
            for (int j = 0; j < N1; j++) if (i & (1 << j)) x ^= A[j];
            if (table.count(x) || bitCount(table[x]) < bitCount(i)) table[x] = i;
        }
        int ans = 0;
        for (int i = 0; i < (1 << N2); i++) {
            int x = 0;
            for (int j = 0; j < N2; j++) if (i & (1 << j)) x ^= A[N1 + j];
            if (table.count(x) && bitCount(ans) < bitCount(table[x]) + bitCount(i)) ans = (i << N1) ^ table[x];
        }
        printf("%d\n", bitCount(ans));
        for (int i = 0; i < N; i++) if (ans & (1 << i)) printf("%d ", i + 1);
        printf("\n");
    }
    return 0;
}
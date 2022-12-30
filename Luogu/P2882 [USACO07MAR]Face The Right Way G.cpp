#include <cstdio>
#include <cstring>

const int inf = 1e9 + 10;

const int maxN = 5000;

int N;
int K, M;
bool F[maxN + 10];
bool D[maxN + 10];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        char ch;
        scanf(" %c", &ch);
        if (ch == 'F') F[i] = 1;
        else F[i] = 0;
    }
    M = inf;
    for (int k = 1; k <= N; k++) {
        std::memset(D, 0, sizeof(D));
        bool facing = false;
        bool ok = true;
        int cnt = 0;
        for (int i = 1; i <= N; i++) {
            facing ^= D[i];
            if ((F[i] ^ facing) == false) {
                if (i + k - 1 > N) {
                    ok = false;
                    break;
                }
                facing ^= true;
                D[i] ^= true;
                D[i + k] ^= true;
                cnt++;
            }
        }
        if (ok) {
            if (M > cnt) {
                M = cnt;
                K = k;
            }
        }
    }
    printf("%d %d\n", K, M);
    return 0;
}
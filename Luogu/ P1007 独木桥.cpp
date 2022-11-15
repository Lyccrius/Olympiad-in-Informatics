#include <cstdio>
#include <algorithm>

const int inf = 0x3f3f3f3f;

int L;
int N;
int pos;

int minT = -inf;
int maxT = -inf;

int main() {
    scanf("%d", &L);
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &pos);
        if (pos <= (L >> 1)) {
            minT = std::max(minT, pos);
            maxT = std::max(maxT, L + 1 - pos);
        } else {
            minT = std::max(minT, L + 1 - pos);
            maxT = std::max(maxT, pos);
        }
    }
    printf("%d %d\n", minT, maxT);
    return 0;
}
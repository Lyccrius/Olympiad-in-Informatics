#include <cstdio>
#include <cstring>

const int maxN = 10000 + 10;

int n;
int depth;
int array[maxN];

bool DFS(int now) {
    if (now == depth) return array[now] == n;
    if (array[now] * (long long)1 << (depth - now) < n) return false;
    bool fail[maxN << 1];
    std::memset(fail, false, sizeof(fail));
    for (int i = now; i >= 1; i--) for (int j = i; j >= 1; j--) {
        int num = array[i] + array[j];
        if (num <= n && num > array[now] && !fail[num]) {
            array[now + 1] = num;
            if (DFS(now + 1)) return true;
            else fail[num] = true;
        }
    }
    return false;
}

void mian() {
    depth = 1;
    while (!DFS(1)) depth++;
    for (int i = 1; i <= depth; i++) {
        printf("%d", array[i]);
        if (i != depth) printf(" ");
    }
    printf("\n");
    return;
}

int main() {
    array[1] = 1;
    while (scanf("%d", &n) && n) mian();
    return 0;
}
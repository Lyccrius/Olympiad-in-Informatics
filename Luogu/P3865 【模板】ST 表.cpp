#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;

int N, M;
int a[maxn];
int l, r;

int f[maxn][50];

void ST_prework() {
   for (int i = 1; i <= N; i++) f[i][0] = a[i];
   int t = log(N) / log(2) + 1;
   for (int j = 1; j < t; j++)
      for (int i = 1; i <= N - (1<<j) + 1; i++)
         f[i][j] = max(f[i][j-1], f[i + (1<<(j-1))][j-1]);
}

int ST_query(int l, int r) {
   int k = log(r - l + 1) / log(2);
   return max(f[l][k], f[r - (1<<k) + 1][k]);
}

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }

    ST_prework();

    while (M--) {
        scanf("%d%d", &l, &r);

        printf("%d\n", ST_query(l, r));
    }

    return 0;
}
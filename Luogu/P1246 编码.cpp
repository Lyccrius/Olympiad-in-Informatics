#include <cstdio>
#include <cstring>

const int maxN = 26 + 10;

char str[maxN];
int f[maxN][maxN];

int main() {
    scanf("%s", str + 1);
    int n = std::strlen(str + 1);
    for (int i = 2; i <= n; i++) if (str[i] <= str[i - 1] || n > 6) {
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= 26; i++) f[i][1] = 1;
    for (int j = 2; j <= 6; j++) {
        for (int i = 26 - j + 1; i >= 1; i--) {
            f[i][j] = f[i + 1][j - 1] + f[i + 1][j];
        }
    }
    int cnt = 0;
    int ans = 0;
    for (int j = n; j >= 1; j--) {
        cnt++;
        for (int i = 1; i <= str[j] - 'a' + 1; i++) {
            ans += f[i][cnt];
        }
    }
    printf("%d\n", ans);
    return 0;
}
#include <cstdio>
#include <cstring>

const int maxN = 80 + 10;

int T;
char str[maxN];
int score[maxN];

int main() {
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        std::memset(score, 0, sizeof(score));
        scanf("%s", str);
        int cnt = 0;;
        int sum = 0;
        for (int i = 0; i < std::strlen(str); i++) {
            if (str[i] == 'O') {
                cnt++;
                sum += cnt;
            } else cnt = 0;
        }
        printf("%d\n", sum);
    }
    return 0;
}
#include <cstdio>
#include <map>

int n;
int a;
int Q;
int m;

std::map<int, int> ball;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        ball[a] = i;
    }
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d", &m);
        if (ball.count(m)) printf("%d\n", ball[m]);
        else printf("%d\n", 0);
    }
    return 0;
}
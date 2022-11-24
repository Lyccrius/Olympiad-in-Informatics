#include <cstdio>
#include <cstring>
#include <queue>

const int maxLen = 1e6 + 10;

char s[maxLen];

int main() {
    scanf("%s", s + 1);
    int len = std::strlen(s + 1);
    std::queue<int> x;
    std::queue<int> y;
    bool zed = false;
    for (int i = 1; i <= len; i++) {
        switch(s[i]) {
            case 'X': {
                x.push(1);
                y.push(0);
                if (zed) {
                    printf("-1");
                    return 0;
                }
                break;
            }
            case 'Y': {
                x.push(0);
                y.push(1);
                if (zed) {
                    printf("-1");
                    return 0;
                }
                break;
            }
            case 'Z': {
                x.push(0);
                y.push(0);
                zed = true;
                break;
            }
        }
    }
    while (!x.empty()) {
        printf("%d", x.front());
        x.pop();
    }
    printf("\n");
    while (!y.empty()) {
        printf("%d", y.front());
        y.pop();
    }
    return 0;
}
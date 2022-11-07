#include <cstdio>
#include <queue>
#include <stack>

const int maxn = 5e5 + 10;

int T;
int n;
int a[maxn << 1];

std::queue<char> ansFront;
std::stack<char> ansBack;
int frontL, frontR;
int backL, backR;

bool check() {
        while (frontL <= frontR || backL <= backR) {
            bool updated = false;
            if (a[frontL] == a[frontR] && frontL < frontR) {
                frontL++;
                frontR--;
                ansFront.push('L');
                ansBack.push('L');
                updated = true;
            } else if (a[frontL] == a[backL] && frontL <= frontR && backL <= backR) {
                frontL++;
                backL++;
                ansFront.push('L');
                ansBack.push('R');
                updated = true;
            } else if (a[backR] == a[frontR] && frontL <= frontR && backL <= backR) {
                backR--;
                frontR--;
                ansFront.push('R');
                ansBack.push('L');
                updated = true;
            } else if (a[backR] == a[backL] && backR != backL) {
                backR--;
                backL++;
                ansFront.push('R');
                ansBack.push('R');
                updated = true;
            }
            if (!updated) break;
        }
        if (frontL < frontR || backL < backR) return false;
        return true;
}

void print() {
        while (!ansFront.empty()) {
            printf("%c", ansFront.front());
            ansFront.pop();
        }
        while (!ansBack.empty()) {
            printf("%c", ansBack.top());
            ansBack.pop();
        }
        printf("\n");
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        while (!ansFront.empty()) ansFront.pop();
        while (!ansBack.empty()) ansBack.pop();
        for (int i = 1; i <= n * 2; i++) scanf("%d", &a[i]);
        for (int i = 2; i <= n * 2; i++) if (a[i] == a[1]) {
            frontL = 2;
            frontR = i - 1;
            backL = i + 1;
            backR = n * 2;
            break;
        }
        ansFront.push('L');
        ansBack.push('L');
        //printf("%d %d %d %d\n", frontL, frontR, backL, backR);
        if (check()) {
            print();
            continue;
        }
        while (!ansFront.empty()) ansFront.pop();
        while (!ansBack.empty()) ansBack.pop();
        for (int i = 1; i < n * 2; i++) if (a[i] == a[2 * n]) {
            frontL = 1;
            frontR = i - 1;
            backL = i + 1;
            backR = n * 2 - 1;
            break;
        }
        ansFront.push('R');
        ansBack.push('L');
        if (check()) {
            print();
            continue;
        }
        printf("-1\n");
    }
    return 0;
}
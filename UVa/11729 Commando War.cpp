#include <cstdio>
#include <algorithm>

const int maxn = 1000 + 10;

int T;

int N;
struct Task {
    int B;
    int J;
    bool operator<(Task other) const {
        return J > other.J;
    }
} task[maxn];

int main() {
    while (scanf("%d", &N) && N) {
        T++;
        for (int i = 1; i <= N; i++) scanf("%d%d", &task[i].B, &task[i].J);
        std::sort(task + 1, task + N + 1);
        int start = 0;
        int ans = 0;
        for (int i = 1; i <= N; i++) {
            start += task[i].B;
            ans = std::max(ans, start + task[i].J);
        }
        printf("Case %d: %d\n", T, ans);
    }
    return 0;
}
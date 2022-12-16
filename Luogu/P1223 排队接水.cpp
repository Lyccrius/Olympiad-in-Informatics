#include <cstdio>
#include <algorithm>

const int maxN = 1000 + 10;

int n;

struct Node {
    int id;
    int t;

    bool operator<(Node other) const {
        return t < other.t;
    }
} person[maxN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &person[i].t), person[i].id = i;
    std::sort(person + 1, person + n + 1);
    for (int i = 1; i <= n; i++) printf("%d ", person[i].id);
    printf("\n");
    double sum = 0;
    for (int i = 1; i <= n; i++) sum += person[i].t * (n - i);
    printf("%.2lf\n", sum / n);
    return 0;
}
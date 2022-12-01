#include <cstdio>
#include <stack>

const int maxN = 250000 + 10;

int n;
int d[maxN];
int w[maxN];
std::stack<int> buildings;
int num;

int main() {
    scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &d[i], &w[i]);
    for (int i = 1; i <= n; i++) {
        while (!buildings.empty() && buildings.top() >= w[i]){
            if (buildings.top() == w[i]) num++;
            buildings.pop();
        }
        buildings.push(w[i]);
    }
	printf("%d\n", n - num);
    return 0;
}
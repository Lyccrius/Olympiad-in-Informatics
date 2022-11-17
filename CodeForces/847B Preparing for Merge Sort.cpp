#include <cstdio>
#include <vector>

const int inf = 0x3f3f3f3f;
const int maxN = 2e5 + 10;

int n;
int a[maxN];
std::vector<int> ans[maxN];
int cnt;

int main() {
    scanf("%d", &n);
    ans[0].push_back(inf);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] < ans[cnt].back()) {
            cnt++;
            ans[cnt].push_back(a[i]);
        } else {
            int l = 1;
            int r = cnt;
            while (l < r) {
                int mid = (l + r) / 2;
                if (ans[mid].back() < a[i]) r = mid;
                else l = mid + 1;
            }
            ans[l].push_back(a[i]);
        }
    }
    for (int i = 1; !ans[i].empty(); i++) {
        for (int j = 0; j < ans[i].size(); j++) printf("%d ", ans[i][j]);
        printf("\n");
    }
    return 0;
}
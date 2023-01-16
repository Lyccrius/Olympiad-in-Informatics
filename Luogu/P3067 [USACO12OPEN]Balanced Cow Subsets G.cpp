#include <iostream>
#include <vector>
#include <map>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 20;

typedef long long lxl;

int n;
int a[maxN + 10];
int ans;
int idx;
//std::map<int, std::vector<int> > v;
std::map<int, int> m;
std::vector<lxl> g[1 << (maxN + 1)];
bool vis[1 << (maxN + 2)];

void DFS(int type, int now, int ed, int sum, int state) {
	if (now > ed) {
		if (type == 0) {
            if (!m.count(sum)) m[sum] = ++idx;
		    g[m[sum]].push_back(state);
            //v[sum].push_back(state);
        } else {
            //for (int i = 0; i < v[sum].size(); i++) vis[v[sum][i] | state] = true;
            if (m.count(sum)) {
			    int t = m[sum];
			    for (int i = 0; i < g[t].size(); i++) vis[g[t][i] | state] = true;
		    }
        }
        return;
	}
    DFS(type, now + 1, ed, sum, state);
	DFS(type, now + 1, ed, sum + a[now], state | (1 << now));
    DFS(type, now + 1, ed, sum - a[now], state | (1 << now));
    return;
}

int main() {
    //promote();
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
    int mid = n >> 1;
	DFS(0, 1, mid, 0, 0);
	DFS(1, mid + 1, n, 0, 0);
	for (int i = 1; i < (1 << (n + 1)); i++) if (vis[i]) ans++;
	std::cout << ans << '\n';
	return 0;
}
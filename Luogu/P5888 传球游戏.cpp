#include <cstdio>
#include <map>

const int maxN = 1e9 + 10;
const int maxM = 200 + 10;
const int maxK = 5e4 + 10;
const int mod = 998244353;

int n, m, k;
int a[maxK], b[maxK];
long long f[2][maxN];
struct node{
	int a, b;
} edge[maxK];
std::map<int, int> mp;
int cnt;
int cur;
long long sum;
long long last;

void Init() {
	mp[1] = 1;
	cnt = 1;
	f[0][1] = 1;
	sum = 1;
	return;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	Init();
	for (int i = 1; i <= k; i++) {
		scanf("%d%d", &a[i], &b[i]);
		if (!mp.count(a[i])) mp[a[i]] = ++cnt;
		if (!mp.count(b[i])) mp[b[i]] = ++cnt;
		edge[i].a = mp[a[i]];
		edge[i].b = mp[b[i]];
	}
	while (m--) {
		last = sum;
		sum = last * (n - 1) % mod;
		for (int i = 1; i <= cnt; i++) f[cur ^ 1][i] = ((last - f[cur][i]) % mod + mod) % mod;
		for (int i = 1; i <= k; i++) if (edge[i].a != edge[i].b) {
			f[cur ^ 1][edge[i].b] = ((f[cur ^ 1][edge[i].b] - f[cur][edge[i].a]) % mod + mod) % mod;
			sum = ((sum - f[cur][edge[i].a]) % mod + mod) % mod;
		}
		cur ^= 1;
	}
	printf("%d", f[cur][1]);
	return 0;
}
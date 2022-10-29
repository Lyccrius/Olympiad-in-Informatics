#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100;

int main() {
    int n, m;
	scanf("%d%d", &n, &m);
	int map[maxn][maxn];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++){
			scanf("%d", &map[i][j]);
		} 
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		long long F[maxn][maxn];
	    for (int j = 1; j <= m; j++) {
	    	F[j][j] = map[i][j] * 2;
	    }
	
	    for (int j = m; j >= 1; j--) {
		    for (int len = 1; j + len - 1 <= m; len++) {
		    	long long q = F[j + 1][j + len - 1] * 2 + map[i][j] * 2;
		    	long long p = F[j][j + len - 1 - 1] * 2 + map[i][j + len - 1] * 2;
		    	F[j][j + len - 1] = std::max(q, p);
		    }
	    }
	
	    ans += F[1][m];
	}
	
	printf("%lld\n", ans);
	
	return 0;
}
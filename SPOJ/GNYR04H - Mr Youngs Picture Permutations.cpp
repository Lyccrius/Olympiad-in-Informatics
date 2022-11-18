#include<cstdio>
#include<cstring>

const int maxN = 30 + 1;

int k;
int n[6];
long long f[maxN][maxN][maxN][maxN][maxN];

int main() {
	while (scanf("%d", &k) != EOF && k) {
	    std::memset(n, 0, sizeof(n));
	    for (int i = 1; i <= k; i++) scanf("%d", &n[i]);
	    std::memset(f, 0, sizeof(f));
	    f[0][0][0][0][0] = 1;
	    for (int a1 = 0; a1 <= n[1]; a1++)
	    	for (int a2 = 0; a2 <= n[2]; a2++)
	    		for (int a3 = 0; a3 <= n[3]; a3++)
	    			for (int a4 = 0; a4 <= n[4]; a4++)
	    				for (int a5 = 0; a5 <= n[5]; a5++) {
        					if (a1 < n[1]) f[a1 + 1][a2][a3][a4][a5] += f[a1][a2][a3][a4][a5];
	    					if (a2 < n[2] && a2 < a1) f[a1][a2 + 1][a3][a4][a5] += f[a1][a2][a3][a4][a5];
	    					if (a3 < n[3] && a3 < a2) f[a1][a2][a3 + 1][a4][a5] += f[a1][a2][a3][a4][a5];
	    					if (a4 < n[4] && a4 < a3) f[a1][a2][a3][a4 + 1][a5] += f[a1][a2][a3][a4][a5];
	    					if (a5 < n[5] && a5 < a4) f[a1][a2][a3][a4][a5 + 1] += f[a1][a2][a3][a4][a5];
	    				}
	    printf("%lld\n", f[n[1]][n[2]][n[3]][n[4]][n[5]]);
    }
	return 0;
}
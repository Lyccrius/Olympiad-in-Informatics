#include <bits/stdc++.h>

using namespace std;

int N, M;

int a[360];
int b[360];
int num[5];

int F[50][50][50][50];

int main() {
	cin >> N >> M;
	
	for (int i = 1; i <= N; i ++) cin >> a[i];
	
	for (int i = 1; i <= M; i ++) cin >> b[i], num[b[i]] ++;
	
	for (int i = 0; i <= num[1]; i ++){
		for (int j = 0; j <= num[2]; j ++){
			for (int k = 0; k <= num[3]; k ++){
				for (int l = 0; l <= num[4]; l ++){
					if (i) F[i][j][k][l] = max(F[i][j][k][l], F[i-1][j][k][l]);
					if (j) F[i][j][k][l] = max(F[i][j][k][l], F[i][j-1][k][l]);
					if (k) F[i][j][k][l] = max(F[i][j][k][l], F[i][j][k-1][l]);
					if (l) F[i][j][k][l] = max(F[i][j][k][l], F[i][j][k][l-1]);

					F[i][j][k][l] += a[1 + i * 1 + j * 2 + k * 3 + l * 4];
				}
			}
		}
	}
	
	cout << F[num[1]][num[2]][num[3]][num[4]] << endl;
	
	return 0;
}
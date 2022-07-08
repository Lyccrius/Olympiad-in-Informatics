#include <bits/stdc++.h>

using namespace std;

int n;

int happy[6010];
int visit[6010];

int root;
vector<int>son[6010];

int F[6010][2];

void DFS(int x){
	F[x][0] = 0;
	F[x][1] = happy[x];
	
	for (int i = 0; i < son[x].size(); i ++) {
		DFS(son[x][i]);
		
		F[x][0] += max(F[son[x][i]][0], F[son[x][i]][1]);
		F[x][1] += F[son[x][i]][0];
	}
	
	return;
}

int main() {
	cin >> n;
	
	for (int i = 1; i <= n; i ++){
		cin >> happy[i];
	}
	
	int l, k;
	for (int i = 1; i < n; i ++){
		cin >> l >> k;
		son[k].push_back(l);
		visit[l] = 1;
	}
	
	for (int i = 1; i <= n; i ++){
		if (!visit[i]) {
			root = i;
			break;
		}
	}
	
	DFS(root);
	
	cout << max(F[root][0], F[root][1]) << endl;
	
	return 0;
}
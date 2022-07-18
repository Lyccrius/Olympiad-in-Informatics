#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10, M = 2 * N;
struct EDGE{
    int to,next;
}edge[M];
int head[N],cnt;
void add(int u,int v){
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
int n;
int size[N];
void dfs(int x,int fa){
    size[x] = 1;
    for(int i = head[x];i;i = edge[i].next){
        int to = edge[i].to;
        if(to==fa)continue;
        dfs(to,x);
        size[x]+=size[to];
    }
}
int main(){
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
        add(v,u);
    }   
    dfs(1,1);
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(n%i)continue;
        int temp = 0;
        for(int j = 1; j <= n; j++)
            if(size[j]%i==0)temp++;
        if(n/i==temp)ans++;
    }
    cout << ans;
    system("pause");
    return 0;
}

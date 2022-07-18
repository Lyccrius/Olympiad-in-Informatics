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
int n,m;
int t[N];
bool check(int T){
    int sum = 0,Cnt,temp = 0;
    for(int i = 1; i <= n; i++){
        sum += t[i];
        if(sum > T)break;
        Cnt = 1;
        temp = 0;
        for(int j = i; j < i+n; j++){
            if(t[j]>T)return 0;
            temp += t[j];
            if(temp>T){
                Cnt++;
                temp = t[j];
            }
        }
        if(Cnt<=m)return 1;
    }
    return 0;
}
int main(){
    cin >> n >> m;
    int l = 1,r = 0;
    for(int i = 1; i <= n; i++){
        cin >> t[i];
        r += t[i];
        t[i+n] = t[i];
    }
    int ans;
    while(l <= r){
        int mid = (l+r)>>1;
        if(check(mid)){ans = mid;r = mid-1;}
        else l = mid+1;
    }
    cout << ans;
    system("pause");
    return 0;
}

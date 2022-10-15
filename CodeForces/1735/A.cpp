#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e9 + 10;
 
typedef pair<int, int> pii;
 
int t;
 
int n;
 
int main() {
 
    scanf("%d", &t);
 
    while (t--) {
        scanf("%d", &n);
        
        printf("%d\n", (n - 3) / 3 - 1);
    }
 
    return 0;
}
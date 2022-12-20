#include <cstdio>
#include <string>
#include <iostream>

int n;
std::string a, b;
int x, y;
int city[676][676];
int ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        std::cin >> a >> b;
        x = (a[0] - 'A') * 26 + a[1] - 'A'; 
        y = (b[0] - 'A') * 26 + b[1] - 'A';
        if (x != y) {
            city[x][y]++;
            ans += city[y][x];
        }
    }
    printf("%d\n", ans);
    return 0;
}
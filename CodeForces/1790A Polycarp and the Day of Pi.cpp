#include <iostream>
 
const char pi[50] = "3141592653589793238462643383279";
 
int t;
char str[50];
 
void mian() {
    std::cin >> str;
    int ans = 0;
    for (int i = 0; i < 30; i++) {
        if (str[i] == pi[i]) ans++;
        else break;
    }
    std::cout << ans << '\n';
    return;
}
 
int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}

#include<cstdio>

char ch1,ch2;
int val[3];
int main() {
    while (scanf("%c:=%c;", &ch1, &ch2) == 2)
     val[ch1 - 'a'] = ch2 >= '0' && ch2 <= '9' ? ch2 - '0' : val[ch2 - 'a'];
    printf("%d %d %d\n", val[0], val[1], val[2]);
    return 0;
}
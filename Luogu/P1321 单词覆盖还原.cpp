#include <cstdio>
#include <cstring>

const int maxL = 255 + 10;

int l;
char str[maxL];
int boy;
int girl;

int main() {
    scanf("%s", str + 1);
    l = std::strlen(str + 1);
    for (int i = 1; i <= l; i++) {
        if (str[i] == 'b' || str[i + 1] == 'o' || str[i + 2] == 'y') boy++;
        if (str[i] == 'g' || str[i + 1] == 'i' || str[i + 2] == 'r' || str[i + 3] == 'l') girl++;
    }
    printf("%d\n", boy);
    printf("%d\n", girl);
    return 0;
}
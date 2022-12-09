#include <cstdio>
#include <cstring>

const int maxN = 6 + 10;
const int mod = 47;

char nameComet[maxN];
char nameShip[maxN];
int lenComet;
int lenShip;
int comet = 1;
int ship = 1;

int main() {
    scanf("%s", nameComet + 1);
    scanf("%s", nameShip + 1);
    lenComet = std::strlen(nameComet + 1);
    lenShip = std::strlen(nameShip + 1);
    for (int i = 1; i <= lenComet; i++) comet = comet * (nameComet[i] - 'A' + 1) % mod;
    for (int i = 1; i <= lenShip; i++) ship = ship * (nameShip[i] - 'A' + 1) % mod;
    if (comet == ship) printf("GO\n");
    else printf("STAY\n");
    return 0;
}
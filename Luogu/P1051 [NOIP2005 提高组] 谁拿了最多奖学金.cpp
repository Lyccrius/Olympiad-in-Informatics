#include <cstdio>
#include <cstring>

const int maxn = 100 + 10;

int N;
struct Student {
    char name[20 + 10];
    int averageScore;
    int commentScore;
    bool cadre;
    bool west;
    int paper;
    int prize;
}student[maxn];

char maxPrizer[20 + 10];
int maxPrize;
int sumPrize;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        char c;
        scanf("%s", student[i].name);
        scanf("%d", &student[i].averageScore);
        scanf("%d", &student[i].commentScore);
        scanf(" %c", &c); student[i].cadre = c == 'Y' ? true : false;
        scanf(" %c", &c); student[i].west = c == 'Y' ? true : false;
        scanf("%d", &student[i].paper);
        if (student[i].averageScore > 80 && student[i].paper) student[i].prize += 8000;
        if (student[i].averageScore > 85 && student[i].commentScore > 80) student[i].prize += 4000;
        if (student[i].averageScore > 90) student[i].prize += 2000;
        if (student[i].averageScore > 85 && student[i].west) student[i].prize += 1000;
        if (student[i].commentScore > 80 && student[i].cadre) student[i].prize += 850;
        if (student[i].prize > maxPrize) {
            std::strcpy(maxPrizer, student[i].name);
            maxPrize = student[i].prize;
        }
        sumPrize += student[i].prize;
    }
    printf("%s\n", maxPrizer);
    printf("%d\n", maxPrize);
    printf("%d\n", sumPrize);
    return 0;
}
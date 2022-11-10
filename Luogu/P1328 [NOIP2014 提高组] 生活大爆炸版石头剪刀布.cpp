#include <cstdio>

int N, NA, NB;
int A[10000], B[10000];

int a, b;
int ansA, ansB;

int main() {
    scanf("%d%d%d", &N, &NA, &NB);
    for (int i = 1; i <= NA; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= NB; i++) scanf("%d", &B[i]);
    for (int i = 1; i <= N; i++) {
        a = a % NA + 1;
        b = b % NB + 1;
        switch (A[a]) {
            case 0: switch(B[b]) {
                case 1: ansB++; break;
                case 2: ansA++; break;
                case 3: ansA++; break;
                case 4: ansB++; break;
            }; break;
            case 1: switch(B[b]) {
                case 0: ansA++; break;
                case 2: ansB++; break;
                case 3: ansA++; break;
                case 4: ansB++; break;
            }; break;
            case 2: switch(B[b]) {
                case 0: ansB++; break;
                case 1: ansA++; break;
                case 3: ansB++; break;
                case 4: ansA++; break;
            }; break;
            case 3: switch(B[b]) {
                case 0: ansB++; break;
                case 1: ansB++; break;
                case 2: ansA++; break;
                case 4: ansA++; break;
            }; break;
            case 4:switch(B[b]) {
                case 0: ansA++; break;
                case 1: ansA++; break;
                case 2: ansB++; break;
                case 3: ansB++; break;
            }; break;
        }
    }
    printf("%d %d", ansA, ansB);
	return 0;
}
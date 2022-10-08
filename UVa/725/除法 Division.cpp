#include <bits/stdc++.h>

int n;

int main() {
	bool printed = false;
	while (scanf("%d", &n) && n) {
		if (printed) {
			printf("\n");
		} else {
		    printed = true;
        }

        int abcde;
        int fghij;
        int used[10];
        bool solved = false;

		for (fghij = 1234; fghij <= 49876; fghij++){ 
			abcde = n * fghij;
            memset(used, 0, sizeof(used));

			if (abcde > 99999){
			    break;
			}

			if (abcde < 10000){
			    continue;
			}

			int x = abcde;
            int y = fghij;

			while (x || y){
				used[x % 10]++;
                used[y % 10]++;
				x /= 10;
                y /= 10;
			}

            bool flag = true;

            for (int i = 0; i < 10; i++) {
                if (used[i] != 1) {
                    flag = false;
                    break;
                }
            }

			if (flag){
				solved = true;

                if (fghij < 10000) {
                    printf("%d / 0%d = %d\n", abcde, fghij, n);
                } else {
                    printf("%d / %d = %d\n", abcde, fghij, n);
                }
			}
		}

		if (!solved){
			printf("There are no solutions for %d.\n", n);
		}
	}

	return 0;
}
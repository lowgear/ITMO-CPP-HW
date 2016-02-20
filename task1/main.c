#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <math.h>

const int MAX_LEN = 60;

typedef struct {
    int x, y;
} pair_i_i;

int main() {
    int n;
    scanf("%d", &n);
    long long *table = (long long *) malloc(n * n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            table[n * i + j] = ((long long)i + 1) * (j + 1);
        }
    }

    pair_i_i b, e;
    //char *max_num = malloc(MAX_LEN);
    while(1) {
        scanf("%d", &b.x);
        if (!b.x) {
            break;
        }
        scanf("%d%d%d", &b.y, &e.x, &e.y);

        //sprintf(max_num, "%lld", table[n * (e.x - 1) + e.y - 1]);
        //int size = (int)strlen(max_num);
        int size = (int)log10(floor((double)table[n * (e.x - 1) + e.y - 1]));

        for (int i = b.x - 1; i < e.x; i++) {
            for (int j = b.y - 1; j < e.y; j++) {
                printf("%*lld ", size, table[n * i + j]);
            }
            printf("\n");
        }
    }

    free(table);

    return 0;
}
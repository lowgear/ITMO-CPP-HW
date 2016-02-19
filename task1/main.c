#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} pair_i_i;

const int MAX_LEN = 64;

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
    for (scanf("%d%d%d%d", &b.x, &b.y, &e.x, &e.y); b.x; scanf("%d%d%d%d", &b.x, &b.y, &e.x, &e.y)) {
        long long max_num = table[n * (e.x - 1) + e.y - 1];

        for (int i = b.x - 1; i < e.x; i++) {
            for (int j = b.y - 1; j < e.y; j++) {
                printf("%*lld ", (int)floor(log10(max_num)) + 1, table[n * i + j]);
            }
            printf("\n");
        }
    }

    free(table);

    return 0;
}
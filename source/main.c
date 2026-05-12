#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const int N = 7;
    int a[N][N];

    srand((unsigned)time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 21 - 10; // числа от -10 до 10
        }
    }

    int zeros_above_main = 0;
    int positives_below_secondary = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j > i && a[i][j] == 0)
                zeros_above_main++;

            if (i + j > N - 1 && a[i][j] > 0)
                positives_below_secondary++;
        }
    }

    printf("Original matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }

    printf("\nZeros above main diagonal: %d\n", zeros_above_main);
    printf("Positive elements below secondary diagonal: %d\n", positives_below_secondary);

    if (zeros_above_main == positives_below_secondary) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = 0;
            }
        }

        printf("\nCounts are equal. Matrix after zeroing:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%4d", a[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}

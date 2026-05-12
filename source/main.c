#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 7

int count_zeros_above_main(int a[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (j > i && a[i][j] == 0)
                count++;
    return count;
}

int count_positives_below_secondary(int a[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i + j > N - 1 && a[i][j] > 0)
                count++;
    return count;
}

void zero_matrix(int a[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 0;
}

void print_matrix(int a[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", a[i][j]);
        printf("\n");
    }
}

int main(void) {
    int a[N][N];

    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = rand() % 21 - 10;

    int zeros   = count_zeros_above_main(a);
    int positives = count_positives_below_secondary(a);

    printf("Original matrix:\n");
    print_matrix(a);

    printf("\nZeros above main diagonal: %d\n", zeros);
    printf("Positive elements below secondary diagonal: %d\n", positives);

    if (zeros == positives) {
        zero_matrix(a);
        printf("\nCounts are equal. Matrix after zeroing:\n");
        print_matrix(a);
    }

    return 0;
}

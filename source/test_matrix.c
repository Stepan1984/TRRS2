#include <stdio.h>
#include <string.h>

#define N 7

/* Копии тестируемых функций */
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

/* Утилиты тестирования */
static int passed = 0, failed = 0;

#define ASSERT_EQ(label, expected, actual)                          \
    do {                                                            \
        if ((expected) == (actual)) {                               \
            printf("[PASS] %s\n", label);                          \
            passed++;                                               \
        } else {                                                    \
            printf("[FAIL] %s: expected %d, got %d\n",             \
                   label, (expected), (actual));                    \
            failed++;                                               \
        }                                                           \
    } while(0)

/*
   TEST 1: Нулей выше главной диагонали нет (все элементы = 1)
*/
void test_zeros_above_main_all_ones(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 1;
    ASSERT_EQ("zeros_above_main: all ones -> 0", 0, count_zeros_above_main(a));
}

/*
   TEST 2: Вся матрица нули — считаем только выше главной
   Выше главной диагонали в 7x7: j > i => 21 элемент
*/
void test_zeros_above_main_all_zeros(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 0;
    /* Треугольник выше главной: 6+5+4+3+2+1 = 21 */
    ASSERT_EQ("zeros_above_main: all zeros -> 21", 21, count_zeros_above_main(a));
}

/*
   TEST 3: Только один ноль в позиции (0,1) — выше диагонали
 */
void test_zeros_above_main_single_zero(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 1;
    a[0][1] = 0;
    ASSERT_EQ("zeros_above_main: single zero at (0,1) -> 1", 1, count_zeros_above_main(a));
}

int main(void) {
    printf("=== Running matrix7 unit tests ===\n\n");

    test_zeros_above_main_all_ones();
    test_zeros_above_main_all_zeros();
    test_zeros_above_main_single_zero();

    printf("\n=== Results: %d passed, %d failed ===\n", passed, failed);
    return ( failed > 0 ) ? 1 : 0;
}

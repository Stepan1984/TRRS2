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

/* ============================================================
   TEST 1: Нулей выше главной диагонали нет (все элементы = 1)
   ============================================================ */
void test_zeros_above_main_all_ones(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 1;
    ASSERT_EQ("zeros_above_main: all ones -> 0", 0, count_zeros_above_main(a));
}

/* ============================================================
   TEST 2: Вся матрица нули — считаем только выше главной
   Выше главной диагонали в 7x7: j > i => 21 элемент
   ============================================================ */
void test_zeros_above_main_all_zeros(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 0;
    /* Треугольник выше главной: 6+5+4+3+2+1 = 21 */
    ASSERT_EQ("zeros_above_main: all zeros -> 21", 21, count_zeros_above_main(a));
}

/* ============================================================
   TEST 3: Только один ноль в позиции (0,1) — выше диагонали
   ============================================================ */
void test_zeros_above_main_single_zero(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 1;
    a[0][1] = 0;
    ASSERT_EQ("zeros_above_main: single zero at (0,1) -> 1", 1, count_zeros_above_main(a));
}

/* ============================================================
   TEST 4: Ноль на главной диагонали (0,0) — не должен считаться
   ============================================================ */
void test_zeros_above_main_diagonal_zero_not_counted(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 1;
    a[0][0] = 0;  /* на диагонали */
    a[3][1] = 0;  /* НИЖЕ диагонали, j < i */
    ASSERT_EQ("zeros_above_main: zeros on/below diagonal not counted -> 0",
              0, count_zeros_above_main(a));
}

/* ============================================================
   TEST 5: Положительных ниже побочной нет (все отрицательные)
   ============================================================ */
void test_positives_below_secondary_all_negative(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = -1;
    ASSERT_EQ("positives_below_secondary: all -1 -> 0", 0,
              count_positives_below_secondary(a));
}

/* ============================================================
   TEST 6: Все элементы = 1, считаем треугольник ниже побочной
   i + j > N-1 => i + j > 6, треугольник: 6+5+4+3+2+1 = 21
   ============================================================ */
void test_positives_below_secondary_all_ones(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 1;
    ASSERT_EQ("positives_below_secondary: all 1 -> 21", 21,
              count_positives_below_secondary(a));
}

/* ============================================================
   TEST 7: Нули не считаются как положительные
   ============================================================ */
void test_positives_below_secondary_zeros_not_positive(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 0;
    ASSERT_EQ("positives_below_secondary: all zeros -> 0", 0,
              count_positives_below_secondary(a));
}

/* ============================================================
   TEST 8: Ручная матрица — проверяем оба счётчика одновременно
   a[0][1]=0 (выше гл.), a[0][2]=0 (выше гл.)
   a[6][5]=1 (ниже поб.), a[5][6]=1 (ниже поб.)
   => zeros=2, positives=2
   ============================================================ */
void test_manual_matrix_equal_counts(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = -1;

    a[0][1] = 0;
    a[0][2] = 0;
    a[6][5] = 1;
    a[5][6] = 1;

    ASSERT_EQ("manual: zeros_above_main -> 2",   2, count_zeros_above_main(a));
    ASSERT_EQ("manual: positives_below_sec -> 2", 2, count_positives_below_secondary(a));
}

/* ============================================================
   TEST 9: zero_matrix() обнуляет все элементы
   ============================================================ */
void test_zero_matrix(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = i * N + j + 1;

    zero_matrix(a);

    int all_zero = 1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i][j] != 0) { all_zero = 0; break; }

    ASSERT_EQ("zero_matrix: all elements become 0", 1, all_zero);
}

/* ============================================================
   TEST 10: Счётчики не равны — матрица не обнуляется
   zeros=1, positives=0 => не равны
   ============================================================ */
void test_counts_not_equal_no_zeroing(void) {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = -1;
    a[0][1] = 0;  /* 1 ноль выше главной */

    int zeros     = count_zeros_above_main(a);
    int positives = count_positives_below_secondary(a);
    int not_equal = (zeros != positives) ? 1 : 0;
    ASSERT_EQ("counts not equal (1 vs 0): no zeroing expected", 1, not_equal);
}

int main(void) {
    printf("=== Running matrix7 unit tests ===\n\n");

    test_zeros_above_main_all_ones();
    test_zeros_above_main_all_zeros();
    test_zeros_above_main_single_zero();
    test_zeros_above_main_diagonal_zero_not_counted();
    test_positives_below_secondary_all_negative();
    test_positives_below_secondary_all_ones();
    test_positives_below_secondary_zeros_not_positive();
    test_manual_matrix_equal_counts();
    test_zero_matrix();
    test_counts_not_equal_no_zeroing();

    printf("\n=== Results: %d passed, %d failed ===\n", passed, failed);
    return (failed > 0) ? 1 : 0;
}

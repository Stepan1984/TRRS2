#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/gauge.h>
#include <prometheus/registry.h>

#include <memory>
#include <string>
#include <thread>
#include <chrono>

#define N 7

int zeros_above_main(int a[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (j > i && a[i][j] == 0)
                count++;
    return count;
}

int positives_below_secondary(int a[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i + j > N - 1 && a[i][j] > 0)
                count++;
    return count;
}

void fill_matrix_random(int a[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = rand() % 21 - 10;
}

void print_matrix(int a[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", a[i][j]);
        printf("\n");
    }
}

void run_logic(int a[N][N]) {
    int z = zeros_above_main(a);
    int p = positives_below_secondary(a);

    printf("Original matrix:\n");
    print_matrix(a);
    printf("Zeros above main diagonal: %d\n", z);
    printf("Positive elements below secondary diagonal: %d\n", p);

    if (z == p) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = 0;
        printf("Counts are equal. Matrix after zeroing:\n");
        print_matrix(a);
    }
}

// ── РЕЖИМ ТЕСТОВ: читаем stdin, выводим результат, выходим ──────────────────
void mode_stdin() {
    int a[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (scanf("%d", &a[i][j]) != 1) {
                fprintf(stderr, "Error: expected %d integers\n", N * N);
                exit(1);
            }
    run_logic(a);
}

// ── РЕЖИМ KUBERNETES: случайная матрица + HTTP-сервер метрик ─────────────────
void mode_server() {
    using namespace prometheus;

    Exposer exposer{"0.0.0.0:8080"};
    auto registry = std::make_shared<Registry>();

    auto& fam_calc = BuildCounter()
        .Name("matrix7_calculations_total")
        .Help("Total number of matrix calculations performed")
        .Register(*registry);
    auto& calc_counter = fam_calc.Add({});

    auto& fam_zeros = BuildGauge()
        .Name("matrix7_zeros_above_main_diagonal")
        .Help("Zeros above main diagonal in last matrix")
        .Register(*registry);
    auto& zeros_gauge = fam_zeros.Add({});

    auto& fam_pos = BuildGauge()
        .Name("matrix7_positives_below_secondary_diagonal")
        .Help("Positive elements below secondary diagonal in last matrix")
        .Register(*registry);
    auto& pos_gauge = fam_pos.Add({});

    auto& fam_zeroed = BuildGauge()
        .Name("matrix7_matrix_zeroed")
        .Help("Whether matrix was zeroed in last calculation (1=yes, 0=no)")
        .Register(*registry);
    auto& zeroed_gauge = fam_zeroed.Add({});

    exposer.RegisterCollectable(registry);
    srand(42);

    printf("matrix7 started in server mode. Metrics at :8080/metrics\n");

    while (true) {
        int a[N][N];
        fill_matrix_random(a);

        int z = zeros_above_main(a);
        int p = positives_below_secondary(a);

        run_logic(a);

        zeros_gauge.Set((double)z);
        pos_gauge.Set((double)p);
        zeroed_gauge.Set(z == p ? 1.0 : 0.0);
        calc_counter.Increment();

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--server") {
        mode_server();
    } else {
        mode_stdin();
    }
    return 0;
}

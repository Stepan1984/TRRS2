#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>
using namespace std;

static int passed = 0, failed = 0;

// Запускает ./matrix7, подаёт matrix на stdin, возвращает stdout
string run_program(const string& matrix_input) {
    string command = "echo \"" + matrix_input + "\" | ../usr/bin/matrix7";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
        throw runtime_error("popen failed");

    char buffer[256];
    string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        result += buffer;
    pclose(pipe);
    return result;
}

void run_test(const string& name, const string& input, const string& expected_substr) {
    string output = run_program(input);
    if (output.find(expected_substr) != string::npos) {
        cout << "[PASS] " << name << "\n";
        passed++;
    } else {
        cout << "[FAIL] " << name << "\n";
        cout << "       Expected to find: \"" << expected_substr << "\"\n";
        cout << "       Got output:       \"" << output.substr(0, 120) << "\"\n";
        failed++;
    }
}

// 7x7 матрица, все элементы = val
string make_matrix(int val) {
    string s;
    for (int i = 0; i < 49; i++) {
        if (i > 0) s += " ";
        s += to_string(val);
    }
    return s;
}

// 7x7 матрица из заданного массива (49 чисел)
string make_matrix_from(int vals[49]) {
    string s;
    for (int i = 0; i < 49; i++) {
        if (i > 0) s += " ";
        s += to_string(vals[i]);
    }
    return s;
}

int main(void) {
    cout << "=== Running matrix7 integration tests ===\n\n";

    // --- ТЕСТ 1: Все элементы = 1, нулей выше главной нет, positives есть
    // zeros=0, positives=21 → не равны, матрица не обнуляется
    run_test("Test 1: all ones — counts not equal, no zeroing",
        make_matrix(1),
        "Zeros above main diagonal: 0");

    // --- ТЕСТ 2: Все элементы = 1 → positives_below_secondary = 21
    run_test("Test 2: all ones — 21 positives below secondary",
        make_matrix(1),
        "Positive elements below secondary diagonal: 21");

    // --- ТЕСТ 3: Все элементы = -1 → zeros=0, positives=0 → равны → обнуление
    run_test("Test 3: all -1 — counts equal (0==0), matrix zeroed",
        make_matrix(-1),
        "Counts are equal. Matrix after zeroing:");

    // --- ТЕСТ 4: Все = 0 → zeros=21, positives=0 → не равны
    run_test("Test 4: all zeros — zeros=21, positives=0, not equal",
        make_matrix(0),
        "Zeros above main diagonal: 21");

    // --- ТЕСТ 5: Вручную: 2 нуля выше главной, 2 положительных ниже побочной
    // Вся матрица = -1, потом [0][1]=0, [0][2]=0, [6][5]=1, [5][6]=1
    // zeros=2, positives=2 → равны → обнуление
    {
        int vals[49];
        for (int i = 0; i < 49; i++) vals[i] = -1;
        // [0][1] = индекс 1, [0][2] = индекс 2
        vals[1] = 0;
        vals[2] = 0;
        // [6][5] = индекс 6*7+5=47, [5][6] = индекс 5*7+6=41
        vals[47] = 1;
        vals[41] = 1;
        run_test("Test 5: manual matrix — zeros==positives==2, zeroed",
            make_matrix_from(vals),
            "Counts are equal. Matrix after zeroing:");
    }

    // --- ТЕСТ 6: Программа выводит "Original matrix:"
    run_test("Test 6: output always contains 'Original matrix:'",
        make_matrix(5),
        "Original matrix:");

    // --- ТЕСТ 7: Некорректный ввод — программа должна вернуть ошибку
    {
        string command = "echo \"1 2 3\" | ../usr/bin/matrix7 2>&1";
        FILE* pipe = popen(command.c_str(), "r");
        char buf[256]; string out;
        while (fgets(buf, sizeof(buf), pipe)) out += buf;
        pclose(pipe);
        if (out.find("Error") != string::npos || out.find("error") != string::npos) {
            cout << "[PASS] Test 7: invalid input reports error\n";
            passed++;
        } else {
            cout << "[FAIL] Test 7: invalid input — expected error message\n";
            failed++;
        }
    }

    cout << "\n=== Results: " << passed << " passed, " << failed << " failed ===\n";
    return (failed > 0) ? 1 : 0;
}

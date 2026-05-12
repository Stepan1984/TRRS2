#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

static int passed = 0, failed = 0;

void run_test(const string& name, int fill_val, const string& expected) {
    string input;
    for (int i = 0; i < 49; i++) {
        if (i > 0) input += " ";
        input += to_string(fill_val);
    }

    string cmd = "echo \"" + input + "\" | ../usr/bin/matrix7";
    FILE* pipe = popen(cmd.c_str(), "r");
    char buf[256]; string output;
    while (fgets(buf, sizeof(buf), pipe)) output += buf;
    pclose(pipe);

    if (output.find(expected) != string::npos) {
        cout << "[PASS] " << name << "\n";
        passed++;
    } else {
        cout << "[FAIL] " << name << "\n";
        cout << "       Expected: \"" << expected << "\"\n";
        failed++;
    }
}

int main(void) {
    run_test("Test 1: all ones — zeros=0",     1,  "Zeros above main diagonal: 0");
    run_test("Test 2: all ones — positives=21", 1,  "Positive elements below secondary diagonal: 21");
    run_test("Test 3: all -1 — zeroed",        -1, "Counts are equal. Matrix after zeroing:");
    run_test("Test 4: all zeros — zeros=21",    0,  "Zeros above main diagonal: 21");

    cout << "\n=== Results: " << passed << " passed, " << failed << " failed ===\n";
    return (failed > 0) ? 1 : 0;
}

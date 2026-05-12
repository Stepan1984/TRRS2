#!/usr/bin/env bash
set -e

BINARY="./usr/bin/matrix7"
PASS=0
FAIL=0

echo "=== [TEST] Running tests ==="

echo "[TEST 1] Binary exists and is executable..."
if [ -x "$BINARY" ]; then
    echo "  PASS"
    PASS=$((PASS+1))
else
    echo "  FAIL: $BINARY not found or not executable"
    FAIL=$((FAIL+1))
fi

echo "[TEST 2] Program exits with code 0..."
"$BINARY" > /dev/null 2>&1
EXIT_CODE=$?
if [ "$EXIT_CODE" -eq 0 ]; then
    echo "  PASS (exit code: $EXIT_CODE)"
    PASS=$((PASS+1))
else
    echo "  FAIL (exit code: $EXIT_CODE)"
    FAIL=$((FAIL+1))
fi

echo "[TEST 3] Output contains 'Original matrix'..."
OUTPUT=$("$BINARY" 2>&1)
if echo "$OUTPUT" | grep -q "Original matrix"; then
    echo "  PASS"
    PASS=$((PASS+1))
else
    echo "  FAIL: 'Original matrix' not found in output"
    FAIL=$((FAIL+1))
fi

echo "[TEST 4] Output contains diagonal stats..."
if echo "$OUTPUT" | grep -q "Zeros above main diagonal:"; then
    echo "  PASS"
    PASS=$((PASS+1))
else
    echo "  FAIL: diagonal stats not found"
    FAIL=$((FAIL+1))
fi

echo "[TEST 5] Output contains secondary diagonal stats..."
if echo "$OUTPUT" | grep -q "Positive elements below secondary diagonal:"; then
    echo "  PASS"
    PASS=$((PASS+1))
else
    echo "  FAIL: secondary diagonal stats not found"
    FAIL=$((FAIL+1))
fi

echo "[TEST 6] Program exits 0 on 5 consecutive runs..."
RUN_FAIL=0
for i in 1 2 3 4 5; do
    "$BINARY" > /dev/null 2>&1
    CODE=$?
    if [ "$CODE" -ne 0 ]; then
        echo "  FAIL on run $i (exit code: $CODE)"
        RUN_FAIL=1
        FAIL=$((FAIL+1))
        break
    fi
done
if [ "$RUN_FAIL" -eq 0 ]; then
    echo "  PASS"
    PASS=$((PASS+1))
fi

echo ""
echo "=== [TEST] Results: $PASS passed, $FAIL failed ==="

if [ "$FAIL" -gt 0 ]; then
    exit 1
fi

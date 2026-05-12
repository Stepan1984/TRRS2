#!/usr/bin/env bash
set -e

echo "=== [TEST] Building and running unit tests ==="

cd source
make test

echo "=== [TEST] Done ==="

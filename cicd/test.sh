#!/usr/bin/env bash
set -e
echo "=== [TEST] Building and running integration tests ==="
cd source
make test
echo "=== [TEST] Done ==="

#!/usr/bin/env bash
set -e

echo "=== [BUILD] Starting build ==="

mkdir -p usr/bin

cd source
make clean
make

cp matrix7 ../usr/bin/matrix7

echo "=== [BUILD] Done: usr/bin/matrix7 ==="

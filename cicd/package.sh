#!/usr/bin/env bash
set -e

echo "=== [PACKAGE] Building .deb package ==="

PKG_NAME="trrs1"
VERSION="1.0"
PKG_DIR="pkg/${PKG_NAME}_${VERSION}"

rm -rf "$PKG_DIR"
mkdir -p "$PKG_DIR/DEBIAN"
mkdir -p "$PKG_DIR/usr/bin"

cp usr/bin/matrix7 "$PKG_DIR/usr/bin/matrix7"
chmod 755 "$PKG_DIR/usr/bin/matrix7"

cp DEBIAN/control "$PKG_DIR/DEBIAN/control"

mkdir -p pkg
dpkg-deb --build "$PKG_DIR" "pkg/${PKG_NAME}_${VERSION}.deb"

echo "=== [PACKAGE] Done: pkg/${PKG_NAME}_${VERSION}.deb ==="

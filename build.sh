#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"
GEN="Ninja"
TYPE="Debug"
JOBS="$(nproc 2>/dev/null || echo 8)"

mode="${1:-build}"

case "$mode" in
  clean)
    rm -rf "$BUILD_DIR"
    echo "[build] cleaned"
    exit 0
    ;;
  build|"")
    ;;
  *)
    echo "Usage: $0 [clean|build]"
    exit 1
    ;;
esac

echo "[build] configuring..."
cmake -S . -B "$BUILD_DIR" -G "$GEN" -DCMAKE_BUILD_TYPE="$TYPE"

echo "[build] building engine..."
cmake --build "$BUILD_DIR" -j"$JOBS"

echo "[build] building shaders..."
cmake --build "$BUILD_DIR" --target Shaders -j"$JOBS"

echo "[build] done"
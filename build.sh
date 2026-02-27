#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"
GEN="Ninja"
TYPE="Debug"
JOBS="$(nproc 2>/dev/null || echo 8)"

mode="${1:-all}"

case "$mode" in
  clean)
    rm -rf "$BUILD_DIR"
    echo "[build] cleaned"
    exit 0
    ;;
  configure)
    cmake -S . -B "$BUILD_DIR" -G "$GEN" -DCMAKE_BUILD_TYPE="$TYPE"
    exit 0
    ;;
esac

# Configure if needed
if [[ ! -f "$BUILD_DIR/CMakeCache.txt" ]]; then
  echo "[build] configuring..."
  cmake -S . -B "$BUILD_DIR" -G "$GEN" -DCMAKE_BUILD_TYPE="$TYPE"
fi

if [[ "$mode" == "shaders" ]]; then
  echo "[build] building shaders..."
  cmake --build "$BUILD_DIR" --target Shaders -j"$JOBS"
  exit 0
fi

echo "[build] building engine..."
cmake --build "$BUILD_DIR" -j"$JOBS"

echo "[build] building shaders..."
cmake --build "$BUILD_DIR" --target Shaders -j"$JOBS"

echo "[build] done"
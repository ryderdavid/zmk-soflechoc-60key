#!/usr/bin/env bash
# Build both Sofle halves (nice!view) and optionally flash.
# Requires: Docker (e.g. colima start), and existing west workspace (run once: see README).
set -e
REPO="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO"

ZEPHYR_DIR="${REPO}/zephyr/share/zephyr-package/cmake"
[ -d "$ZEPHYR_DIR" ] || { echo "Run a full 'west init -l config && west update' first (e.g. via Docker)."; exit 1; }

echo "=== Building LEFT half (nice_view + mod-status) ==="
rm -rf build
docker run --rm -v "$REPO:/workspace" -w /workspace -e HOME=/tmp zmkfirmware/zmk-dev-arm:stable bash -c \
  "west build -s zmk/app -b nice_nano@2.0.0 -- \
  -DZephyr_DIR=/workspace/zephyr/share/zephyr-package/cmake \
  -DSHIELD='sofle_left nice_view_adapter nice_view' \
  -DZMK_CONFIG=/workspace/config \
  -DSNIPPET=studio-rpc-usb-uart \
  -DZMK_EXTRA_MODULES=/workspace/zmk-modules/mod-status \
  -DOVERLAY_CONFIG=/workspace/zmk-modules/mod-status/disable_nice_view_widget.conf"
cp build/zephyr/zmk.uf2 "firmware/firmware/sofle_left-nice_nano@2.0.0-zmk.uf2"
cp build/zephyr/zmk.uf2 "firmware/firmware/sofle_left nice_view_adapter nice_view-nice_nano@2.0.0-zmk.uf2"
echo "Left firmware saved."

echo "=== Building RIGHT half (nice_view) ==="
rm -rf build
docker run --rm -v "$REPO:/workspace" -w /workspace -e HOME=/tmp zmkfirmware/zmk-dev-arm:stable bash -c \
  "west build -s zmk/app -b nice_nano@2.0.0 -- \
  -DZephyr_DIR=/workspace/zephyr/share/zephyr-package/cmake \
  -DSHIELD='sofle_right nice_view_adapter nice_view' \
  -DZMK_CONFIG=/workspace/config"
cp build/zephyr/zmk.uf2 "firmware/firmware/sofle_right-nice_nano@2.0.0-zmk.uf2"
cp build/zephyr/zmk.uf2 "firmware/firmware/sofle_right nice_view_adapter nice_view-nice_nano@2.0.0-zmk.uf2"
echo "Right firmware saved."

echo ""
echo "=== Flash ==="
echo "1. Connect LEFT half via USB, double-tap reset. When NICENANO appears, run:"
echo "   cp \"$REPO/firmware/firmware/sofle_left-nice_nano@2.0.0-zmk.uf2\" /Volumes/NICENANO/"
echo "2. Connect RIGHT half, double-tap reset. When NICENANO appears, run:"
echo "   cp \"$REPO/firmware/firmware/sofle_right-nice_nano@2.0.0-zmk.uf2\" /Volumes/NICENANO/"
echo ""
if [ -d /Volumes/NICENANO ]; then
  echo "NICENANO is mounted. Flashing LEFT now..."
  cp "$REPO/firmware/firmware/sofle_left-nice_nano@2.0.0-zmk.uf2" /Volumes/NICENANO/
  echo "Left flashed. Connect RIGHT half, double-tap reset, then run:"
  echo "  cp \"$REPO/firmware/firmware/sofle_right-nice_nano@2.0.0-zmk.uf2\" /Volumes/NICENANO/"
fi

#!/bin/bash
# Build firmware for Sofle with ticker modifications
# This script builds both left and right halves with the nice_view display

set -e

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}Building Sofle firmware with ticker enhancements...${NC}"

# Ensure west workspace is initialized
if [ ! -d ".west" ]; then
    echo "Initializing west workspace..."
    west init -l config
    west update
fi

# Build command template
build_half() {
    local HALF=$1
    local SHIELD="sofle_${HALF} nice_view_adapter nice_view"
    
    echo -e "\n${GREEN}Building ${HALF} half...${NC}"
    
    # Use Docker if available, otherwise try local west build
    if command -v docker &> /dev/null; then
        docker run --rm \
            -v "${REPO_ROOT}:/workspace" \
            -w /workspace \
            zmkfirmware/zmk-dev-arm:stable \
            bash -c "west build -s zmk/app -b nice_nano@2.0.0 -d build/${HALF} --pristine -- \
                -DSHIELD='${SHIELD}' \
                -DZMK_CONFIG=/workspace/config \
                -DZephyr_DIR=/workspace/zephyr/share/zephyr-package/cmake"
        
        # Copy firmware to firmware directory
        mkdir -p firmware
        cp "build/${HALF}/zephyr/zmk.uf2" "firmware/sofle_${HALF}_nice_view.uf2"
        echo -e "${GREEN}Firmware saved to firmware/sofle_${HALF}_nice_view.uf2${NC}"
    else
        # Local build (requires Zephyr SDK installed)
        west build -s zmk/app -b nice_nano@2.0.0 -d "build/${HALF}" --pristine -- \
            -DSHIELD="${SHIELD}" \
            -DZMK_CONFIG="${REPO_ROOT}/config" \
            -DZephyr_DIR="${REPO_ROOT}/zephyr/share/zephyr-package/cmake"
        
        mkdir -p firmware
        cp "build/${HALF}/zephyr/zmk.uf2" "firmware/sofle_${HALF}_nice_view.uf2"
        echo -e "${GREEN}Firmware saved to firmware/sofle_${HALF}_nice_view.uf2${NC}"
    fi
}

# Build both halves
build_half "left"
build_half "right"

echo -e "\n${GREEN}✓ Build complete!${NC}"
echo -e "${BLUE}Firmware files:${NC}"
ls -lh firmware/sofle_*_nice_view.uf2

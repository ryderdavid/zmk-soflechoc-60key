# Ticker with Per-Character Modifiers Implementation

## Overview

This implementation extends the ZMK nice!view display ticker to show modifier keys (Ctrl, Alt, Cmd) that were pressed with each character. The ticker now displays as 4 vertical cells, each showing a stack of modifier glyphs above the character.

## Changes Made

### 1. Data Model (`zmk/app/boards/shields/nice_view/widgets/util.h`)

Added to `status_state` struct:
```c
/* Ticker: last 4 chars in typing order (oldest first), and last key position */
char ticker_chars[5];
uint8_t ticker_len; /* 0..4 */
uint32_t ticker_position;
uint8_t ticker_mods[4]; /* modifier byte per char slot (Ctrl/Alt/Cmd, no Shift) */
```

### 2. Custom Font (`zmk/app/boards/shields/nice_view/widgets/mac_symbols_8.c`)

Created an 8x8 pixel, 1bpp font with three modifier glyphs:
- **⌃** (U+2303) - Control: Narrow chevron with 2px stroke
- **⌥** (U+2325) - Alt/Option: Diagonal line with dot/dash, 2px stroke  
- **⌘** (U+2318) - Command/GUI: Small square with corner loops, 2px stroke

All glyphs use ~2px stroke weight to match the ticker character font.

### 3. Status Widget Logic (`zmk/app/boards/shields/nice_view/widgets/status.c`)

#### Added Functions:

**`keycode_to_char(usage_page, keycode, mods)`**
- Maps HID keyboard keycodes to printable ASCII characters
- Handles US QWERTY layout with Shift modifier
- Returns 0 for non-printable keys

**`ticker_push_char_mod(widget, c, mod_byte)`**
- Stores character and modifier byte in parallel arrays
- Maintains typing order (oldest at [0], newest at [3])
- Shifts both arrays when buffer is full

**`ticker_update_position(widget, position)`**
- Updates the last key position for display

#### Event Listeners:

**`ticker_keycode_listener`**
- Triggers on key release
- Extracts character using `keycode_to_char`
- Strips Shift from mod byte (already reflected in character)
- Stores Ctrl/Alt/Cmd modifier state
- Defers redraw to display work queue

**`ticker_position_listener`**
- Triggers on key press
- Updates position display
- Defers redraw to display work queue

#### Display Layout Changes:

**Position ID:**
- Moved to top-right of WPM graph
- Position: `(50, 24)`, right-aligned, 16px width
- Format: `"%02u"` (two-digit number)

**Ticker Cells:**
- 4 cells, 10px wide each, starting at x=2
- Character at y=54 (bottom of cell)
- Modifiers stacked above:
  - Ctrl at y=30
  - Alt at y=38 (or 30 if no Ctrl)
  - Cmd at y=46 (or 30/38 if previous mods absent)
- Only active modifiers are drawn
- Shift is excluded (already in character)

### 4. Build Configuration (`zmk/app/boards/shields/nice_view/CMakeLists.txt`)

Added `mac_symbols_8.c` to the build:
```cmake
zephyr_library_sources(widgets/mac_symbols_8.c)
```

## Visual Layout

```
WPM Graph (68x42, starting at y=21):
┌─────────────────────────────────────────────────────────────────┐
│                                                           [02]   │ ← Position ID (top-right)
│                                                                  │
│ [⌘]  [⌃]  [⌥]  [ ]                                              │ ← Modifier row 1 (y=30)
│ [⌥]  [⌥]  [ ]  [ ]                                              │ ← Modifier row 2 (y=38)
│ [ ]  [ ]  [ ]  [ ]                                              │ ← Modifier row 3 (y=46)
│ [h]  [e]  [l]  [l]                                         [42] │ ← Characters (y=54) + WPM
│ ─────────────────────────────────                               │ ← WPM graph line
└─────────────────────────────────────────────────────────────────┘
```

## Modifier Encoding

Each ticker slot stores a byte with these bits:
- bit 0: Ctrl (left or right)
- bit 2: Alt (left or right)  
- bit 3: Cmd/GUI (left or right)

Shift bits are masked out since Shift affects the character itself.

## Building

### Using Docker (Recommended):
```bash
./scripts/build-ticker.sh
```

### Manual Build:
```bash
# Left half
west build -s zmk/app -b nice_nano@2.0.0 -d build/left --pristine -- \
  -DSHIELD="sofle_left nice_view_adapter nice_view" \
  -DZMK_CONFIG=/workspace/config \
  -DZephyr_DIR=/workspace/zephyr/share/zephyr-package/cmake

# Right half  
west build -s zmk/app -b nice_nano@2.0.0 -d build/right --pristine -- \
  -DSHIELD="sofle_right nice_view_adapter nice_view" \
  -DZMK_CONFIG=/workspace/config \
  -DZephyr_DIR=/workspace/zephyr/share/zephyr-package/cmake
```

Firmware will be in `build/{left,right}/zephyr/zmk.uf2`

## Testing

After flashing:
1. Type some characters with modifiers (e.g., Cmd+C, Ctrl+Alt+T)
2. Watch the ticker display the last 4 keystrokes
3. Each cell should show the modifiers above the character
4. Position code updates in top-right of WPM graph

## Thread Safety

All display updates are deferred to `zmk_display_work_q()` to prevent UI freezes during fast typing. This was critical in the previous ticker implementation.

## Files Modified

```
zmk/app/boards/shields/nice_view/
├── CMakeLists.txt                    # Added mac_symbols_8.c to build
└── widgets/
    ├── util.h                        # Added ticker state fields
    ├── status.c                      # Added ticker logic and rendering
    └── mac_symbols_8.c               # NEW: 8px modifier font
```

## Commit

The changes to the `zmk` workspace are committed as:
```
commit f5feea12
Add ticker with per-character modifiers
```

To apply these changes to your local ZMK fork, you'll need to commit the zmk/ directory changes.

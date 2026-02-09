# ZMK Sofle Choc 60-Key Configuration

You are inside a ZMK firmware configuration repo for the **Sofle Choc 60-key** split ergonomic keyboard. This file gives you everything you need to understand, edit, and build the keymap.

---

## Hardware Profile

| Property | Value |
|----------|-------|
| Board | `nice_nano@2.0.0` (nRF52840-based) |
| Shield | `sofle_left` / `sofle_right` |
| Display | nice!view on LEFT half only (via `nice_view_adapter nice_view`); RIGHT half has no display |
| Keys | 60 (30 per half) |
| Encoders | 2 (one per half, EC11) |
| Connectivity | Bluetooth 5.0 (split wireless) |
| MCU | nRF52840 (ARM Cortex-M4F) |
| Firmware | ZMK (Zephyr RTOS) |
| Studio | Enabled (`CONFIG_ZMK_STUDIO=y`) |
| Pointing | Enabled (`CONFIG_ZMK_POINTING=y`) |

---

## File Map

| File | Purpose |
|------|---------|
| `config/sofle.keymap` | **THE KEYMAP** - all layers, bindings, combos, behaviors |
| `config/sofle.conf` | Kconfig feature toggles (display, encoders, BT, sleep, etc.) |
| `config/west.yml` | West manifest pointing to zmk-firmware |
| `build.yaml` | GitHub Actions build matrix (which board+shield combos to build) |
| `.github/workflows/build.yml` | CI workflow that builds firmware on push |
| `boards/shields/.gitkeep` | Placeholder for custom shield overlays |
| `docs/behaviors.md` | ZMK behavior reference (kp, mt, lt, mo, bt, etc.) |
| `docs/keycodes.md` | Complete keycode reference table |
| `docs/layout.md` | Physical layout diagram with position numbers |
| `profiles/*.keymap` | Named keymap profiles (snapshots of sofle.keymap) |
| `config/sofle.json` | Physical layout (QMK info.json format) for keymap-drawer |
| `keymap_drawer.config.yaml` | keymap-drawer config (labels, combos, display settings) |
| `keymap-drawer/` | Auto-generated SVG, YAML, and PNG output from keymap-drawer |
| `.github/workflows/draw.yml` | CI workflow that renders keymap SVGs on keymap changes |

---

## Physical Layout (60 keys)

The Sofle Choc 60-key is a split keyboard with 30 keys per half.

```
LEFT HALF                                          RIGHT HALF
,-------------------------------------------.     ,-------------------------------------------.
|  0  |  1  |  2  |  3  |  4  |  5  |           |  6  |  7  |  8  |  9  | 10  | 11  |
|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
| 12  | 13  | 14  | 15  | 16  | 17  |           | 18  | 19  | 20  | 21  | 22  | 23  |
|-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
| 24  | 25  | 26  | 27  | 28  | 29  |           | 30  | 31  | 32  | 33  | 34  | 35  |
|-----+-----+-----+-----+-----+-----+-----.     ,-----+-----+-----+-----+-----+-----+-----|
| 36  | 37  | 38  | 39  | 40  | 41  | 42  |     | 43  | 44  | 45  | 46  | 47  | 48  | 49  |
`-----+-----+-----+-----+-----+-----+-----'     `-----+-----+-----+-----+-----+-----+-----'
            | 50  | 51  | 52  | 53  | 54  |     | 55  | 56  | 57  | 58  | 59  |
            `-----------------------------------' `-----------------------------------'
```

### Row Breakdown

| Row | Positions | Count | Description |
|-----|-----------|-------|-------------|
| 0 (Number) | 0-11 | 12 | Top row (6 left + 6 right) |
| 1 (Upper) | 12-23 | 12 | QWERTY row |
| 2 (Home) | 24-35 | 12 | Home row (ASDF...) |
| 3 (Lower) | 36-49 | 14 | Bottom row + 1 encoder key per side |
| 4 (Thumb) | 50-59 | 10 | Thumb cluster (5 per hand) |

### Default Layer (position -> key)

```
LEFT:  ` 1 2 3 4 5                    RIGHT: 6 7 8 9 0 -
       TAB Q W E R T                         Y U I O P BSPC
       LSFT A S D F G                        H J K L ; '
       LCTL Z X C V B [               ] N M , . / RSFT
             GUI ALT CTL LWR SPC       ENT RSE CTL ALT GUI
```

---

## ZMK Binding Syntax

Every key position in a layer gets a **binding**. A binding is a behavior reference with arguments.

### Core Behaviors

| Syntax | Name | Description | Example |
|--------|------|-------------|---------|
| `&kp KEYCODE` | Key Press | Press and release a key | `&kp A`, `&kp LSHFT` |
| `&mt MOD KEY` | Mod-Tap | Hold = modifier, Tap = key | `&mt LSHFT A` (hold=shift, tap=A) |
| `&lt LAYER KEY` | Layer-Tap | Hold = activate layer, Tap = key | `&lt 1 SPACE` (hold=layer1, tap=space) |
| `&mo LAYER` | Momentary Layer | Hold to activate layer | `&mo 1` |
| `&tog LAYER` | Toggle Layer | Tap to toggle layer on/off | `&tog 2` |
| `&sl LAYER` | Sticky Layer | Next keypress on different layer | `&sl 1` |
| `&sk MODIFIER` | Sticky Key | Next keypress gets modifier | `&sk LSHFT` |
| `&trans` | Transparent | Fall through to layer below | `&trans` |
| `&none` | None | No action | `&none` |
| `&gresc` | Grave-Escape | Tap=ESC, Shift+tap=` | `&gresc` |
| `&caps_word` | Caps Word | Auto-capitalize until non-alpha | `&caps_word` |
| `&key_repeat` | Key Repeat | Repeat last keypress | `&key_repeat` |

### Bluetooth Behaviors

| Syntax | Description |
|--------|-------------|
| `&bt BT_CLR` | Clear current BT profile |
| `&bt BT_CLR_ALL` | Clear all BT profiles |
| `&bt BT_SEL 0` | Select BT profile 0 (0-4) |
| `&bt BT_NXT` | Next BT profile |
| `&bt BT_PRV` | Previous BT profile |

### Power & Display

| Syntax | Description |
|--------|-------------|
| `&ext_power EP_TOG` | Toggle external power |
| `&ext_power EP_ON` | External power on |
| `&ext_power EP_OFF` | External power off |
| `&studio_unlock` | Unlock ZMK Studio |

### Encoder Bindings

Encoders use `sensor-bindings` per layer:
```
sensor-bindings = <&inc_dec_kp C_VOL_UP C_VOL_DN &inc_dec_kp PG_UP PG_DN>;
```
Format: `&inc_dec_kp CLOCKWISE_KEY COUNTERCLOCKWISE_KEY` (left encoder, then right encoder).

---

## Key Abbreviation Table

### Modifiers
| Full Name | ZMK Code | Alias |
|-----------|----------|-------|
| Left Shift | `LSHFT` | `LEFT_SHIFT`, `LSHIFT` |
| Right Shift | `RSHFT` | `RIGHT_SHIFT`, `RSHIFT` |
| Left Control | `LCTRL` | `LEFT_CONTROL` |
| Right Control | `RCTRL` | `RIGHT_CONTROL` |
| Left Alt | `LALT` | `LEFT_ALT` |
| Right Alt | `RALT` | `RIGHT_ALT` |
| Left GUI (Cmd/Win) | `LGUI` | `LEFT_GUI`, `LWIN`, `LCMD` |
| Right GUI | `RGUI` | `RIGHT_GUI`, `RWIN`, `RCMD` |

### Common Keys
| Key | ZMK Code |
|-----|----------|
| Escape | `ESC` or `ESCAPE` |
| Backspace | `BSPC` or `BACKSPACE` |
| Delete | `DEL` or `DELETE` |
| Enter/Return | `RET` or `ENTER` or `RETURN` |
| Tab | `TAB` |
| Space | `SPACE` |
| Caps Lock | `CLCK` or `CAPS` or `CAPSLOCK` |

### Numbers
| Key | ZMK Code |
|-----|----------|
| 1-9, 0 | `N1` through `N9`, `N0` |

### Symbols
| Symbol | ZMK Code |
|--------|----------|
| `-` | `MINUS` |
| `=` | `EQUAL` |
| `[` | `LBKT` or `LEFT_BRACKET` |
| `]` | `RBKT` or `RIGHT_BRACKET` |
| `\` | `BSLH` or `BACKSLASH` |
| `;` | `SEMI` or `SEMICOLON` |
| `'` | `SQT` or `SINGLE_QUOTE` or `APOSTROPHE` |
| `,` | `COMMA` |
| `.` | `DOT` or `PERIOD` |
| `/` | `FSLH` or `SLASH` or `FORWARD_SLASH` |
| `` ` `` | `GRAVE` |
| `!` | `EXCL` or `EXCLAMATION` |
| `@` | `AT` or `AT_SIGN` |
| `#` | `HASH` or `POUND` |
| `$` | `DLLR` or `DOLLAR` |
| `%` | `PRCNT` or `PERCENT` |
| `^` | `CARET` |
| `&` | `AMPS` or `AMPERSAND` |
| `*` | `ASTRK` or `ASTERISK` or `STAR` |
| `(` | `LPAR` or `LEFT_PARENTHESIS` |
| `)` | `RPAR` or `RIGHT_PARENTHESIS` |
| `_` | `UNDER` or `UNDERSCORE` |
| `+` | `PLUS` |
| `{` | `LBRC` or `LEFT_BRACE` |
| `}` | `RBRC` or `RIGHT_BRACE` |
| `\|` | `PIPE` |
| `~` | `TILDE` |

### Function Keys
`F1` through `F24`

### Navigation
| Key | ZMK Code |
|-----|----------|
| Up | `UP` or `UP_ARROW` |
| Down | `DOWN` or `DOWN_ARROW` |
| Left | `LEFT` or `LEFT_ARROW` |
| Right | `RIGHT` or `RIGHT_ARROW` |
| Home | `HOME` |
| End | `END` |
| Page Up | `PG_UP` or `PAGE_UP` |
| Page Down | `PG_DN` or `PAGE_DOWN` |
| Insert | `INS` or `INSERT` |
| Print Screen | `PSCRN` or `PRINTSCREEN` |
| Scroll Lock | `SLCK` or `SCROLL_LOCK` |
| Pause | `PAUSE_BREAK` |

### Media Keys
| Function | ZMK Code |
|----------|----------|
| Volume Up | `C_VOL_UP` |
| Volume Down | `C_VOL_DN` |
| Mute | `C_MUTE` |
| Play/Pause | `C_PP` or `C_PLAY_PAUSE` |
| Next Track | `C_NEXT` |
| Previous Track | `C_PREV` |
| Stop | `C_STOP` |
| Brightness Up | `C_BRI_UP` |
| Brightness Down | `C_BRI_DN` |

---

## Keymap File Format

The keymap file (`config/sofle.keymap`) uses Devicetree syntax:

```c
#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>
// ... other includes

#define BASE 0
#define LOWER 1
// ... layer defines

/ {
    conditional_layers { ... };  // Layers activated by combining other layers
    combos { ... };              // Key combos (press multiple keys = different action)
    behaviors { ... };           // Custom behavior definitions

    keymap {
        compatible = "zmk,keymap";

        layer_name {
            display-name = "name";
            bindings = <
                // Row 0: 12 bindings (positions 0-11)
                // Row 1: 12 bindings (positions 12-23)
                // Row 2: 12 bindings (positions 24-35)
                // Row 3: 14 bindings (positions 36-49, includes encoder keys 42,43)
                // Row 4: 10 bindings (positions 50-59, thumb cluster)
            >;
            sensor-bindings = <&inc_dec_kp KEY1 KEY2 &inc_dec_kp KEY3 KEY4>;
        };
    };
};
```

### Binding Count Per Layer
Each layer MUST have exactly **60 bindings** arranged as:
- Row 0: 12 keys
- Row 1: 12 keys
- Row 2: 12 keys
- Row 3: 14 keys (6 + encoder + encoder + 6)
- Row 4: 10 keys (5 left thumb + 5 right thumb)
- **Total: 60**

### Current Layers

| Index | Define | Display Name | Purpose |
|-------|--------|-------------|---------|
| 0 | `BASE` | "default" | Main QWERTY layer |
| 1 | `LOWER` | "lower" | Symbols, F-keys |
| 2 | `RAISE` | "raise" | Navigation, editing |
| 3 | `ADJUST` | "adjust" | Bluetooth, power, system (activated by LOWER+RAISE) |
| 4 | `extra_layer` | "extra1" | Extra layer (currently mostly empty) |

### Combos

| Name | Keys | Action |
|------|------|--------|
| backspace | 31+32 (K+L on home row) | Backspace |
| delete | 27+33 (D+;) | Delete |
| esc | 25+41 (S+B) | Escape |

---

## Build Commands

### GitHub Actions (Recommended)
Push to the repo and GitHub Actions builds firmware automatically via `.github/workflows/build.yml`. Download the `.uf2` files from the Actions artifacts.

### Local Docker Build

Prerequisites: Docker (via Colima on macOS or Docker Desktop).

```bash
# Start Colima if needed
colima start

# Build left half (with nice_view + Studio)
docker run --rm \
  -v "$(pwd):/workspace" \
  -w /workspace \
  zmkfirmware/zmk-dev-arm:stable \
  bash -c "west init -l config && west update && \
    west build -s zmk/app -b nice_nano@2.0.0 -- \
    -DSHIELD='sofle_left nice_view_adapter nice_view' \
    -DZMK_CONFIG=/workspace/config \
    -DSNIPPET=studio-rpc-usb-uart"

# Build right half (with nice_view)
docker run --rm \
  -v "$(pwd):/workspace" \
  -w /workspace \
  zmkfirmware/zmk-dev-arm:stable \
  bash -c "west init -l config && west update && \
    west build -s zmk/app -b nice_nano@2.0.0 -- \
    -DSHIELD='sofle_right nice_view_adapter nice_view' \
    -DZMK_CONFIG=/workspace/config"

# Build left half (without nice_view, with Studio)
docker run --rm \
  -v "$(pwd):/workspace" \
  -w /workspace \
  zmkfirmware/zmk-dev-arm:stable \
  bash -c "west init -l config && west update && \
    west build -s zmk/app -b nice_nano@2.0.0 -- \
    -DSHIELD=sofle_left \
    -DZMK_CONFIG=/workspace/config \
    -DSNIPPET=studio-rpc-usb-uart"

# Build right half (without nice_view)
docker run --rm \
  -v "$(pwd):/workspace" \
  -w /workspace \
  zmkfirmware/zmk-dev-arm:stable \
  bash -c "west init -l config && west update && \
    west build -s zmk/app -b nice_nano@2.0.0 -- \
    -DSHIELD=sofle_right \
    -DZMK_CONFIG=/workspace/config"
```

The `.uf2` file will be at `build/zephyr/zmk.uf2` after each build.

---

## Flash Process

1. **Connect** the keyboard half via USB
2. **Enter bootloader**: Double-tap the reset button on the nice!nano
3. **Mount**: The board appears as a USB drive named `NICENANO`
4. **Copy firmware**:
   ```bash
   # macOS
   cp build/zephyr/zmk.uf2 /Volumes/NICENANO/
   ```
5. **Wait**: The board auto-reboots after the file is copied
6. **Repeat** for the other half

Flash order does not matter. Both halves must be flashed with matching firmware for split communication to work.

**This build uses:**
- **Left half**: `sofle_left nice_view_adapter nice_view` (has display)
- **Right half**: `sofle_right` (no display)

---

## Profiles System

The `profiles/` directory stores named keymap configurations as complete `.keymap` file snapshots. This lets you maintain multiple layouts (e.g., coding, gaming, Colemak) and switch between them.

### Profile file format

Each profile is saved as `profiles/<name>.keymap` with a metadata comment at the top:

```c
/*
 * Profile: <name>
 * Description: <one-line description>
 * Created: <ISO date>
 * Based on: <parent profile or "scratch">
 */
```

The rest of the file is a complete, valid `sofle.keymap`.

### Operations

- **Save**: Snapshot `config/sofle.keymap` -> `profiles/<name>.keymap` (with metadata header)
- **Load**: Copy `profiles/<name>.keymap` -> `config/sofle.keymap` (strip metadata, backup first)
- **List**: Show all profiles with names, descriptions, dates, and which is currently active
- **Diff**: Compare any two profiles (or current vs. a profile) layer-by-layer
- **Rename/Delete**: Manage saved profiles

### Rules

- Always backup `config/sofle.keymap` before loading a profile
- When loading, strip the metadata comment so `config/sofle.keymap` is a clean ZMK keymap
- When listing, detect which profile matches current keymap by content comparison
- Profile names: lowercase alphanumeric + hyphens, no spaces

---

## ASCII Layout Rendering

When rendering layer previews, **always** use the canonical template at `docs/ascii-template.txt`. Never construct ASCII layouts from scratch.

**Workflow:**
1. Read `docs/ascii-template.txt`
2. For each key position, convert the ZMK binding to a 4-char label using `docs/ascii-abbreviations.md`
3. Replace each `{NN}` placeholder with the corresponding label
4. Replace `{ENC_L}` and `{ENC_R}` with encoder rotation descriptions
5. Output the filled template as a code block, prefixed with `Layer: display-name (INDEX)`

This ensures consistent alignment across all renders — especially the encoder keys (positions 42/43) in row 3 and the thumb cluster indentation.

---

## Natural Language Translation Rules

When the user describes key changes in plain English, follow these rules:

1. **Identify the position**: Map user descriptions to position numbers using the layout diagram
   - "top-left" = position 0
   - "Q key" = position 13 (where Q is on QWERTY)
   - "left thumb, innermost" = position 54
   - "right thumb, outermost" = position 55

2. **Identify the action**:
   - "make X do Y" = replace binding at position with `&kp Y`
   - "holding X acts as Y, tapping X stays as Z" = `&mt Y Z` (mod-tap) or `&lt LAYER Z` (layer-tap)
   - "swap X and Y" = exchange the bindings at both positions
   - "put media controls on raise layer" = edit the RAISE layer bindings

3. **Identify the layer**: Default to BASE (layer 0) unless the user specifies otherwise

4. **Generate the binding**: Use the behavior and keycode tables above to produce valid ZMK syntax

5. **Validate**: Ensure the layer still has exactly 60 bindings after the change

6. **Render**: After every keymap edit, regenerate the SVG and PNG visualizations:
   ```bash
   # Re-parse and draw full SVG
   keymap -c keymap_drawer.config.yaml parse -z config/sofle.keymap 2>/dev/null > keymap-drawer/sofle.yaml
   keymap -c keymap_drawer.config.yaml draw keymap-drawer/sofle.yaml -j config/sofle.json -o keymap-drawer/sofle.svg

   # Full keymap PNG
   rsvg-convert keymap-drawer/sofle.svg -o keymap-drawer/sofle.png -w 1600

   # Per-layer PNGs (for inline terminal preview)
   for layer in default lower raise adjust numlk; do
     keymap -c keymap_drawer.config.yaml draw keymap-drawer/sofle.yaml -j config/sofle.json -s "$layer" -o "/tmp/sofle-${layer}.svg"
     rsvg-convert "/tmp/sofle-${layer}.svg" -o "keymap-drawer/sofle-${layer}.png" -w 1200
   done
   ```
   Then show the affected layer(s) inline using `Read` on the per-layer PNG files in `keymap-drawer/`.
   Open the full keymap PNG in Preview with `open keymap-drawer/sofle.png` if the user wants the complete view.

---

## Links

- [ZMK Documentation](https://zmk.dev/docs)
- [ZMK Keycodes](https://zmk.dev/docs/keymaps/list-of-keycodes)
- [ZMK Behaviors](https://zmk.dev/docs/keymaps/behaviors)
- [ZMK Studio](https://zmk.studio)
- [KeyboardHoarders Guide](https://keyboardhoarders.com/blog)
- [KeyboardHoarders Store](https://keyboardhoarders.com)

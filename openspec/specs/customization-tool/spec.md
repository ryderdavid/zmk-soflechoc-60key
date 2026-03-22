# ZMK Keyboard Customization Tool Specification

This specification covers the ZMK keyboard customization tooling: the `/zmk` Claude Code command, keymap-drawer visualization pipeline, build/flash workflow, profile management system, and safety rules.

---

## /zmk Command (Claude Code Skill)

The `/zmk` command is defined at `.claude/commands/zmk.md`. It is an interactive menu-driven interface for managing the keyboard configuration.

### Menu System

10 options:

1. **View Layout** -- render ASCII layout using `docs/ascii-template.txt` template
2. **Map Keys** -- AI-powered natural language to ZMK binding translation
3. **Combos** -- view/add/remove combo definitions
4. **Macros** -- create macro sequences
5. **Layers** -- add/rename/manage layers
6. **Build** -- compile firmware via Docker
7. **Flash** -- step-by-step flash instructions
8. **Bluetooth** -- BT profile management
9. **Settings** -- toggle sofle.conf options
10. **Profiles** -- save/load/switch/diff keymap profiles

### AI Key Mapping Pipeline (Option 2)

Flow:

1. Profile context check
2. Show current layer
3. User describes change in English
4. Translate to ZMK syntax
5. Show diff
6. Confirm
7. Backup and write
8. Render visualization
9. Sync profile
10. Offer next action

Translation rules:

- Identify position from description (key name, position number, or spatial reference)
- Identify action (simple key, hold-tap, swap, layer change)
- Identify target layer (default: BASE)
- Generate valid ZMK binding syntax
- Validate 60 bindings per layer after edit

### Profile Management (Option 10)

Profiles are stored in `profiles/<name>.keymap` as complete keymap snapshots with metadata headers:

```c
/*
 * Profile: <name>
 * Description: <one-line description>
 * Created: <ISO date>
 * Updated: <ISO date>
 * Based on: <parent profile or "scratch">
 */
```

Operations: Save, Load, New (fork), List, Diff, Rename, Delete.

Active profile detection: compare `config/sofle.keymap` content against all `profiles/` files, stripping metadata before comparison.

Current profiles: `default`, `macos`, `colemak`, `corne-canon`, `enthium` (with `engram` being added).

---

## Keymap Visualization Pipeline

Tool: keymap-drawer (Python CLI).

### Pipeline

```
config/sofle.keymap --> parse --> keymap-drawer/sofle.yaml --> draw --> sofle.svg --> rsvg-convert --> sofle.png
```

### Commands

```bash
# Parse keymap to YAML
keymap -c keymap_drawer.config.yaml parse -z config/sofle.keymap > keymap-drawer/sofle.yaml

# Draw full SVG
keymap -c keymap_drawer.config.yaml draw keymap-drawer/sofle.yaml -j config/sofle.json -o keymap-drawer/sofle.svg

# Full keymap PNG (1600px wide)
rsvg-convert keymap-drawer/sofle.svg -o keymap-drawer/sofle.png -w 1600

# Per-layer PNGs (1200px wide, SVGs go to /tmp)
for layer in qwerty bvhzql enthium numbers nav adjust fkeys mouse prec; do
  keymap -c keymap_drawer.config.yaml draw keymap-drawer/sofle.yaml \
    -j config/sofle.json -s "$layer" -o "/tmp/sofle-${layer}.svg"
  rsvg-convert "/tmp/sofle-${layer}.svg" -o "keymap-drawer/sofle-${layer}.png" -w 1200
done
```

### Configuration (keymap_drawer.config.yaml)

- dark_mode: auto
- shrink_wide_legends: 7
- Drop shadow on keys via `svg_extra_style`
- Glyph sources: Material Design Icons, Tabler Icons
- Modifier display: macOS style (Cmd, Opt, Ctl, Sft)
- Special combinations: Hyper = Ctrl+Alt+GUI+Shift, Meh = Ctrl+Alt+Shift
- Raw binding map: custom labels for `td_*`, hyper, mouse movement, etc.
- `zmk_preamble`: defines needed for keymap-drawer's parser (`KEYMAP_DRAWER` guard, pointing defs, behavior stubs)
- Physical layout: `config/sofle.json` (QMK info.json format)

### CI Workflow

`.github/workflows/draw.yml` renders keymap SVGs on push when keymap files change.

### Important Notes

- `&middot;` HTML entity breaks rsvg-convert -- use the literal `·` character instead.
- rsvg-convert path: `/opt/homebrew/bin/rsvg-convert`
- The Read tool renders images in Claude's context only, NOT in the user's terminal -- always use the `open` command instead.
- Per-layer SVGs go to `/tmp` (intermediate). PNGs go to `keymap-drawer/`.

---

## ASCII Layout Rendering

Template: `docs/ascii-template.txt`
Abbreviation rules: `docs/ascii-abbreviations.md`

Workflow:

1. Read the template.
2. For each key position, convert the ZMK binding to a 4-char label using the abbreviation rules.
3. Replace each `{NN}` placeholder with the corresponding label.
4. Replace `{ENC_L}` and `{ENC_R}` with encoder rotation descriptions.
5. Output as a code block prefixed with `Layer: display-name (INDEX)`.

**Critical: always use the template. Never construct ASCII layouts from scratch.**

---

## Build Pipeline

### GitHub Actions (Primary)

Push to the repo triggers `.github/workflows/build.yml`. Download artifacts via:

```bash
gh run download <run-id> --repo ryderdavid/zmk-soflechoc-60key --dir firmware
```

Firmware lands in `firmware/firmware/*.uf2`.

### Local Docker Build

Requires Docker (via Colima on macOS).

- **Left half**: `sofle_left nice_view_adapter nice_view` with `studio-rpc-usb-uart` snippet
- **Right half**: `sofle_right` (no display)

```bash
# Start Colima if needed
colima start

# Build left half
docker run --rm \
  -v "$(pwd):/workspace" \
  -w /workspace \
  zmkfirmware/zmk-dev-arm:stable \
  bash -c "west init -l config && west update && \
    west build -s zmk/app -b nice_nano@2.0.0 -- \
    -DSHIELD='sofle_left nice_view_adapter nice_view' \
    -DZMK_CONFIG=/workspace/config \
    -DSNIPPET=studio-rpc-usb-uart"

# Build right half
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

## Flash Workflow

1. Double-tap reset on the nice_nano. It mounts as a USB drive named `NICENANO`.
2. Copy `settings_reset.uf2` first (clears Studio overrides from flash).
3. Wait for reboot, double-tap reset again.
4. Copy the regular firmware `.uf2`.
5. Repeat for the other half.
6. Flash order between halves does not matter.

macOS `cp` to NICENANO throws cosmetic `xattr`/`fchmod` errors -- these are harmless. The board reboots mid-copy.

---

## Layer Architecture (9 Layers)

| Index | Define | Display Name | Purpose |
|-------|--------|-------------|---------|
| 0 | `QWERTY` | "qwerty" | Default QWERTY alpha layer |
| 1 | `ENGRAM` | "bvhzql" | Engram alternative alpha layout |
| 2 | `ENTHIUM` | "enthium" | Enthium alternative alpha layout |
| 3 | `NUMBERS` | "numbers" | Numbers and symbols |
| 4 | `NAV` | "nav" | Navigation and editing |
| 5 | `ADJUST` | "adjust" | Bluetooth, power, system (activated by NAV + NUMBERS) |
| 6 | `FKEYS` | "fkeys" | Function keys F1-F24 |
| 7 | `MOUSE` | "mouse" | Mouse movement and buttons |
| 8 | `PREC` | "prec" | Precision/scroll control |

### Conditional Layer

ADJUST (5) is activated by holding NAV (4) and NUMBERS (3) simultaneously.

### Layout Cycle

The alpha layers cycle via a toggle: QWERTY -> Engram -> Enthium -> QWERTY.

---

## Safety Rules

1. **Backup before edit**: `cp config/sofle.keymap config/sofle.keymap.bak`
2. **Always show diff and confirm** before writing changes.
3. **Validate 60 bindings per layer** after every edit.
4. **Render visualization** after every keymap change.
5. **Parse carefully** -- if the keymap cannot be parsed, show raw content and ask for help.
6. **Preserve formatting** (indentation, comment style).
7. **Do not touch `#include` lines** unless adding new behavior types.
8. **Test syntax validity** before writing.

---

## File Map

| File | Purpose |
|------|---------|
| `config/sofle.keymap` | The keymap -- all 9 layers, bindings, combos, behaviors |
| `config/sofle.conf` | Kconfig feature toggles |
| `config/sofle.json` | Physical layout for keymap-drawer |
| `keymap_drawer.config.yaml` | keymap-drawer config |
| `keymap-drawer/` | Generated SVG, YAML, PNG output |
| `profiles/*.keymap` | Named keymap profile snapshots |
| `docs/ascii-template.txt` | Canonical ASCII layout template |
| `docs/ascii-abbreviations.md` | Key label abbreviation rules |
| `docs/behaviors.md` | ZMK behavior reference |
| `docs/keycodes.md` | Complete keycode reference table |
| `docs/layout.md` | Physical layout diagram with position numbers |
| `.claude/commands/zmk.md` | /zmk command definition |
| `build.yaml` | GitHub Actions build matrix |
| `.github/workflows/build.yml` | CI firmware build workflow |
| `.github/workflows/draw.yml` | CI keymap drawing workflow |

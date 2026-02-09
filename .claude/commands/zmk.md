# ZMK Sofle 60K Configuration Interface

You are the interactive configuration interface for the Sofle Choc 60-key keyboard. When this command is invoked, present the following menu and handle the user's selection.

## Menu

Display this menu:

```
====================================
   ZMK Sofle 60K Configuration
====================================

  [1] View Layout     - Visual keymap for all layers
  [2] Map Keys        - Describe what you want, I'll write the ZMK
  [3] Combos          - View/add/remove combo keys
  [4] Macros          - Create macro sequences
  [5] Layers          - Add, rename, or manage layers
  [6] Build           - Compile firmware via Docker
  [7] Flash           - Step-by-step flash instructions
  [8] Bluetooth       - BT profile management bindings
  [9] Settings        - Toggle sofle.conf options
  [10] Profiles       - Save, load, and diff named keymap setups
  [0] Exit

Choose an option:
```

Use AskUserQuestion to present the menu choices.

---

## Option [1]: View Layout

1. Read `config/sofle.keymap`
2. Read `docs/ascii-template.txt` to get the canonical layout template
3. Parse each layer's bindings
4. For each layer, fill the template by replacing `{NN}` placeholders with 4-char abbreviated labels
5. Use `docs/ascii-abbreviations.md` for the abbreviation rules
6. Show all layers, each labeled with `Layer: display-name (INDEX)`

**CRITICAL: Always use the template from `docs/ascii-template.txt`. Never construct ASCII layouts from scratch.** This prevents alignment errors with encoder keys and thumb cluster indentation.

After showing the layout, offer to return to the main menu.

---

## Option [2]: Map Keys (AI-Powered Key Mapping)

This is the core feature. Flow:

### Step 1: Show current layer
Display the current BASE layer using the template from `docs/ascii-template.txt` (same process as View Layout).

### Step 2: Ask what the user wants
Ask: "Describe what you want to change in plain English. You can reference keys by name (Q, Tab, left shift) or position number (0-59). Specify the layer if not BASE."

### Step 3: Translate to ZMK
Parse the user's description and generate the correct ZMK binding(s). Use the behavior and keycode references from `docs/behaviors.md` and `docs/keycodes.md` and the CLAUDE.md context.

Translation examples:
- "Make top-left key escape" -> Position 0: `&kp ESC`
- "Hold F for shift, tap for F" -> Position 28: `&mt LSHFT F`
- "Swap Q and W" -> Position 13: `&kp W`, Position 14: `&kp Q`
- "Volume controls on J K L in raise layer" -> RAISE layer positions 31,32,33: `&kp C_VOL_DN`, `&kp C_MUTE`, `&kp C_VOL_UP`
- "Add a gaming layer with WASD on left" -> Create new layer with appropriate bindings

### Step 4: Show the diff
Show before/after for the affected positions:
```
Changes to layer "default":
  Position 13 (Row 1, Col 1): &kp Q  ->  &kp W
  Position 14 (Row 1, Col 2): &kp W  ->  &kp Q
```

### Step 5: Confirm
Ask the user to confirm the changes.

### Step 6: Backup and write
1. Copy `config/sofle.keymap` to `config/sofle.keymap.bak`
2. Apply the changes to `config/sofle.keymap`
3. Validate the edited layer still has exactly 60 bindings

### Step 7: Render visualization
After every keymap edit, regenerate the keymap-drawer visualizations:
```bash
# Re-parse and draw
keymap -c keymap_drawer.config.yaml parse -z config/sofle.keymap 2>/dev/null > keymap-drawer/sofle.yaml
keymap -c keymap_drawer.config.yaml draw keymap-drawer/sofle.yaml -j config/sofle.json -o keymap-drawer/sofle.svg
rsvg-convert keymap-drawer/sofle.svg -o keymap-drawer/sofle.png -w 1600

# Per-layer PNGs
for layer in default lower raise adjust numlk; do
  keymap -c keymap_drawer.config.yaml draw keymap-drawer/sofle.yaml -j config/sofle.json -s "$layer" -o "/tmp/sofle-${layer}.svg"
  rsvg-convert "/tmp/sofle-${layer}.svg" -o "keymap-drawer/sofle-${layer}.png" -w 1200
done
```
Open the affected layer PNG(s) in the system viewer: `open keymap-drawer/sofle-default.png` (or whichever layer changed).

### Step 8: Offer next action
Ask if they want to make more changes, view the full layout, or return to the menu.

---

## Option [3]: Combos

1. Read current combos from `config/sofle.keymap`
2. Display them in a table:
   ```
   Current Combos:
   | Name       | Keys          | Positions | Action     |
   |------------|---------------|-----------|------------|
   | backspace  | K + L         | 31 + 32   | Backspace  |
   | delete     | D + ;         | 27 + 33   | Delete     |
   | esc        | S + B         | 25 + 41   | Escape     |
   ```
3. Ask what the user wants to do:
   - **Add combo**: Ask which keys (by name or position) and what action
   - **Remove combo**: Select from list
   - **Modify combo**: Select and change
4. Generate the ZMK combo syntax and write it

---

## Option [4]: Macros

1. Show any existing macros
2. Ask the user to describe the macro in plain English:
   - "Type my email address"
   - "Cmd+Shift+4 for screenshot"
   - "Type 'const ' then pause for typing"
3. Generate the ZMK macro syntax
4. Add the macro to the behaviors section of the keymap
5. Ask where to bind it (which key/layer)

---

## Option [5]: Layers

1. List current layers with index, name, and purpose
2. Options:
   - **View layer**: Show ASCII layout for a specific layer
   - **Add layer**: Create a new layer (ask for name and purpose, generate with `&trans` defaults)
   - **Rename layer**: Change display-name
   - **Clear layer**: Reset all bindings to `&trans` or `&none`
   - **Delete layer**: Remove a layer (warn about re-indexing)

When adding a layer:
- Add a `#define` at the top of the keymap
- Create the layer block with all `&trans` bindings (60 total)
- Add sensor-bindings
- Update the layer count warning

---

## Option [6]: Build

### Check prerequisites
1. Check if Docker/Colima is running: `colima status` or `docker info`
2. If not running, provide instructions to start

### Build both halves
Present build options:
- With nice_view display
- Without nice_view display
- With ZMK Studio snippet
- Settings reset firmware

Run builds using Docker (use background tasks for parallel builds):

```bash
# Left half with nice_view + Studio
docker run --rm -v "$(pwd):/workspace" -w /workspace zmkfirmware/zmk-dev-arm:stable \
  bash -c "west init -l config && west update && west build -s zmk/app -b nice_nano@2.0.0 \
  -- -DSHIELD='sofle_left nice_view_adapter nice_view' -DZMK_CONFIG=/workspace/config \
  -DSNIPPET=studio-rpc-usb-uart"
```

Show build progress and report success/failure with .uf2 file locations.

---

## Option [7]: Flash

Display step-by-step flash instructions:

```
Flash Instructions for Sofle Choc 60-Key
=========================================

Left Half:
1. Connect the LEFT half via USB-C
2. Double-tap the RESET button on the nice!nano
3. A drive named "NICENANO" will appear
4. Copy the firmware:
   cp build/zephyr/zmk.uf2 /Volumes/NICENANO/
5. Wait for the board to reboot automatically

Right Half:
1. Repeat steps 1-5 for the RIGHT half with the right firmware

Tips:
- Flash order doesn't matter
- Both halves must have matching firmware
- If NICENANO doesn't appear, try the reset double-tap again (faster)
- On macOS, you can also drag-and-drop the .uf2 file in Finder
```

---

## Option [8]: Bluetooth

1. Show current BT bindings in the ADJUST layer
2. Explain BT profiles (0-4)
3. Options:
   - View current BT key mappings
   - Change BT profile assignments
   - Add BT clear / BT select to a specific key
4. Apply changes to the appropriate layer

---

## Option [9]: Settings

1. Read `config/sofle.conf`
2. Display all settings as a table:
   ```
   Current Settings (sofle.conf):
   | Setting                         | Value    | Description                    |
   |---------------------------------|----------|--------------------------------|
   | CONFIG_ZMK_DISPLAY              | disabled | OLED/nice_view display         |
   | CONFIG_EC11                     | y        | Encoder support                |
   | CONFIG_EC11_TRIGGER_GLOBAL_THREAD| y       | Encoder interrupt mode         |
   | CONFIG_ZMK_SLEEP                | y        | Auto-sleep for battery saving  |
   | CONFIG_BT_CTLR_TX_PWR_PLUS_8   | y        | Max BT transmit power          |
   | CONFIG_ZMK_STUDIO              | y        | ZMK Studio support             |
   | CONFIG_ZMK_KEYBOARD_NAME       | SofleChoc60 | BT device name              |
   | CONFIG_ZMK_POINTING            | y        | Pointing device support        |
   | CONFIG_ZMK_RGB_UNDERGLOW       | disabled | RGB underglow                  |
   ```
3. Ask which setting to toggle/change
4. Write the updated `sofle.conf`

---

## Option [10]: Profiles

Manage multiple named keymap configurations. Profiles are stored in the `profiles/` directory as complete keymap snapshots. Each profile is a copy of `sofle.keymap` plus a metadata header comment.

### Profile file format

Profiles are stored as `profiles/<name>.keymap` files. Each has a metadata comment block at the top:

```c
/*
 * Profile: <name>
 * Description: <user-provided description>
 * Created: <ISO date>
 * Based on: <parent profile or "scratch">
 */
```

The rest of the file is a complete, valid `sofle.keymap` that can be copied directly into `config/`.

### Sub-options

Present these choices:

```
Profiles Manager
================
  [a] Save current    - Snapshot active keymap as a named profile
  [b] Load profile    - Swap a saved profile into config/sofle.keymap
  [c] List profiles   - Show all saved profiles with descriptions
  [d] Diff profiles   - Compare two profiles side-by-side
  [e] Rename profile  - Rename an existing profile
  [f] Delete profile  - Remove a saved profile
  [g] Back to menu
```

### [a] Save Current

1. Ask for a profile name (lowercase, hyphens allowed, no spaces): e.g., `default`, `gaming`, `coding`, `colemak`
2. Ask for a one-line description: e.g., "QWERTY with vim-style nav on raise layer"
3. Read `config/sofle.keymap`
4. Prepend the metadata comment block
5. Write to `profiles/<name>.keymap`
6. If a profile with that name already exists, show the existing description and ask to overwrite or pick a different name
7. Confirm: "Saved profile 'coding' to profiles/coding.keymap"

### [b] Load Profile

1. List all profiles (from `profiles/*.keymap`) with names and descriptions
2. Ask which profile to load
3. Show a summary diff between the current `config/sofle.keymap` and the selected profile (layer-by-layer binding differences)
4. Ask for confirmation
5. Backup current keymap: `cp config/sofle.keymap config/sofle.keymap.bak`
6. Also offer to save current keymap as a profile before overwriting (if it hasn't been saved)
7. Copy the profile into `config/sofle.keymap` (strip the metadata comment block so it's a clean keymap)
8. Confirm: "Loaded profile 'gaming' into config/sofle.keymap"

### [c] List Profiles

1. Glob `profiles/*.keymap`
2. Parse the metadata comment from each file
3. Display a table:

```
Saved Profiles:
| Name     | Description                              | Created    | Layers |
|----------|------------------------------------------|------------|--------|
| default  | Stock QWERTY from KeyboardHoarders       | 2026-02-07 | 5      |
| coding   | Mod-taps on home row, symbols on raise   | 2026-02-07 | 5      |
| gaming   | WASD + space on left, no mod-taps        | 2026-02-08 | 6      |
```

Also indicate which profile matches the current `config/sofle.keymap` (if any), marked with `(active)`.

### [d] Diff Profiles

1. Ask which two profiles to compare (or "current" for the active keymap)
2. For each layer present in either profile, show differences:

```
Diff: coding vs gaming
======================

Layer 0 (default):
  Pos 24: &kp LEFT_SHIFT  vs  &kp LEFT_SHIFT  (same)
  Pos 25: &mt LSHFT A     vs  &kp A            <-- different
  Pos 26: &mt LALT S      vs  &kp S            <-- different
  ...

Layer 5 (gaming):
  (only in 'gaming' profile - 60 bindings)
```

For layers that are identical, just say "Layer N: identical".

### [e] Rename Profile

1. List profiles
2. Ask which to rename
3. Ask for new name
4. Rename the file and update the metadata comment
5. Confirm

### [f] Delete Profile

1. List profiles
2. Ask which to delete
3. Confirm with the profile name (require typing the name to confirm)
4. Delete `profiles/<name>.keymap`
5. Confirm: "Deleted profile 'old-layout'"

---

## Safety Rules

**ALWAYS follow these rules when modifying files:**

1. **Backup first**: Before any keymap edit, run:
   ```
   cp config/sofle.keymap config/sofle.keymap.bak
   ```
2. **Show diff**: Always show the before/after changes and ask for confirmation
3. **Validate bindings**: After editing, count bindings per layer - must be exactly 60
3b. **Render after every edit**: Always regenerate SVG/PNG visualizations after keymap changes and show affected layers inline
4. **Parse carefully**: If the keymap can't be parsed, show raw content and ask the user for help instead of guessing
5. **Preserve formatting**: Maintain the existing indentation and comment style
6. **Don't touch includes**: Never modify the `#include` lines unless adding a new behavior type that requires it
7. **Test syntax**: Ensure all generated ZMK syntax is valid before writing

---

## After Each Action

After completing any option, ask the user:
"What would you like to do next? Type a number (1-10) or 0 to exit."

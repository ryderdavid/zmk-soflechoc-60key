## Context

The corne-canon profile establishes a pattern for dual-alpha layouts: Gallium (layer 1) is a toggle overlay that replaces alpha keys via explicit bindings and inherits everything else via `&trans`. Adding Enthium follows this pattern, with the layout **mirrored** so that left-hand letters go to the right and vice versa — placing R on the left thumb (user prefers Space on right thumb).

Enthium v14 is a 34-key alpha layout. The Sofle's number row (Row 0) is untouched. Enthium alphas map to Rows 1-3.

## Goals / Non-Goals

**Goals:**
- Add mirrored Enthium v14 as a toggle alpha overlay
- CAGS home row mods on the mirrored home row letters
- Caps toggle and Windows mode conditional layers
- Layout-aware combos for mouse toggle and fat-finger protection
- Cycle toggle: QWERTY → Gallium → Enthium → QWERTY (replaces current layout_toggle combo)
- Base layer thumb row changes (affects all profiles)
- Cross-thumb misfire protection on NAV/SYMBOLS layers
- Profile and spec artifacts

**Non-Goals:**
- Word chords for Enthium (deferred)
- Modifying existing layout-config platform behaviors or timings

## Decisions

### 1. Mirrored Enthium layout

Original Enthium v14 and its mirror:

```
         ORIGINAL                      MIRRORED
    Left        Right             Left        Right
R1: q y o u =   x l d p z        z p d l x   = u o y q
R2: b c i a e   k h t n s        w s n t h   - e a i c
R3: ' , . ; /   j m g f v        v f g m j   / ; . , '
Thumb:          r                 r
```

The mirror moves vowels (E A I) to the right hand and consonants (S N T H) to the left. R goes to left thumb.

### 2. Sofle position mapping (mirrored Enthium)

**Row 0** (positions 0-11): all `&trans` — number row unchanged.

**Row 1** (positions 12-23):
| Pos | Key | Binding | Notes |
|-----|-----|---------|-------|
| 12 | - | `&trans` | Inherit Tab/Nav from base |
| 13 | Z | `&kp Z` | |
| 14 | P | `&kp P` | |
| 15 | D | `&kp D` | |
| 16 | L | `&kp L` | |
| 17 | X | `&kp X` | |
| 18 | = | `&kp EQUAL` | Enthium programming key |
| 19 | U | `&kp U` | |
| 20 | O | `&kp O` | |
| 21 | Y | `&kp Y` | |
| 22 | Q | `&kp Q` | |
| 23 | - | `&trans` | Inherit - from base |

**Row 2 / Home** (positions 24-35) with CAGS HRM:
| Pos | Key | Binding | Mod | Notes |
|-----|-----|---------|-----|-------|
| 24 | W | `&lts NAV W` | hold=Nav | Outer left, layer-tap |
| 25 | S | `&hml LCTRL S` | Ctrl | CAGS pinky |
| 26 | N | `&hml LALT N` | Alt | CAGS ring |
| 27 | T | `&hml_g LGUI T` | GUI | CAGS middle (gui variant) |
| 28 | H | `&hml LSHFT H` | Shift | CAGS index |
| 29 | K | `&lts NUMBERS K` | hold=Num | Inner left, layer-tap |
| 30 | - | `&lts NUMBERS MINUS` | hold=Num | Inner right, layer-tap |
| 31 | E | `&hmr RSHFT E` | Shift | CAGS index |
| 32 | A | `&hmr_g RGUI A` | GUI | CAGS middle (gui variant) |
| 33 | I | `&hmr RALT I` | Alt | CAGS ring |
| 34 | C | `&hmr RCTRL C` | Ctrl | CAGS pinky |
| 35 | B | `&lts NAV B` | hold=Nav | Outer right, layer-tap |

**Row 3 / Bottom** (positions 36-49):
| Pos | Key | Binding | Notes |
|-----|-----|---------|-------|
| 36 | - | `&trans` | Inherit td_shift |
| 37 | V | `&kp V` | |
| 38 | F | `&kp F` | |
| 39 | G | `&kp G` | |
| 40 | M | `&kp M` | |
| 41 | J | `&lts MOUSE J` | hold=Mouse |
| 42 | - | `&trans` | Encoder |
| 43 | - | `&trans` | Encoder |
| 44 | / | `&kp FSLH` | |
| 45 | ; | `&kp SEMI` | |
| 46 | . | `&kp DOT` | |
| 47 | , | `&kp COMMA` | |
| 48 | ' | `&kp SQT` | |
| 49 | - | `&trans` | Inherit mt(Rshft,/) |

### 3. Thumb row (Enthium layer)

```
50        51        52        53             54        55             56             57        58        59
&trans    &trans    &trans    &lts SYM R     &trans    &trans         &trans         &trans    &trans    &trans
(Ctrl)    (Alt)     (GUI)    hold=Sym       (Mouse/   (Sym/Enter     (Nav/Space     (Cmd)     (Alt)     (Fkey)
                             tap=R          Enter)    from base∆)    from base∆)
```

Position 53: `&lts SYMBOLS R` — hold=Symbols, tap=R. This is the only Enthium-specific thumb override. All others inherit from base via `&trans`.

### 4. Base layer changes (affect ALL profiles)

These changes go into the QWERTY base layer (layer 0) and propagate to all profiles via `&trans`:

| Pos | Current | New | Reason |
|-----|---------|-----|--------|
| 54 | `&lts NAV ENTER` | `&lts MOUSE ENTER` | Mouse layer access on left thumb |
| 57 | `&enter_mash_proof RGUI ENTER` | `&kp RGUI` | Remove Enter from middle right thumb entirely |

### 5. Cross-thumb misfire protection

To prevent accidental Enter/Space when holding an adjacent layer-tap thumb:

| Layer | Pos | Current | New | Reason |
|-------|-----|---------|-----|--------|
| NAV (3) | 55 | `&trans` | `&none` | Prevent Enter while holding Nav at 56 |
| SYMBOLS (4) | 56 | `&trans` | `&none` | Prevent Space while holding Sym at 55 |

### 6. Cycle toggle combo

The existing `layout_toggle` combo (positions 46+47+48+49, `&tog GALLIUM`) becomes a cycle: QWERTY → Gallium → Enthium → QWERTY.

**Implementation:** Replace `&tog GALLIUM` with a macro that checks current state:
- If neither Gallium nor Enthium active: activate Gallium (`&tog GALLIUM`)
- If Gallium active: deactivate Gallium, activate Enthium (`&tog GALLIUM`, `&tog ENTHIUM`)
- If Enthium active: deactivate Enthium (`&tog ENTHIUM`)

ZMK doesn't have conditional macros, so the simplest approach is a tap-dance or just cycle through `&tog` calls:
- Single combo press: `&tog GALLIUM` (toggles Gallium)
- But this doesn't cycle to Enthium...

**Alternative:** Use three separate combos on the same positions, each restricted to specific layers:
- `layout_to_gallium`: positions 46+47+48+49, layers=<QWERTY>, action=`&tog GALLIUM`
- `layout_to_enthium`: positions 46+47+48+49, layers=<GALLIUM>, action: macro that does `&tog GALLIUM` then `&tog ENTHIUM`
- `layout_to_qwerty`: positions 46+47+48+49, layers=<ENTHIUM>, action=`&tog ENTHIUM`

This requires a macro for the Gallium→Enthium transition (must toggle off Gallium and toggle on Enthium atomically). ZMK macros can do this.

### 7. New layer indices

Current: 15 layers (0-14). Add:
- Layer 15: `ENTHIUM` — mirrored alpha toggle overlay
- Layer 16: `ENTHIUM_CAPS` — shifted mirrored Enthium alphas (conditional: ENTHIUM + CAPS_DISPLAY)
- Layer 17: `ENTHIUM_WIN` — Ctrl↔GUI swap for mirrored Enthium (conditional: ENTHIUM + WINMODE)

Conditional layer rules:
- ENTHIUM + CAPS_DISPLAY → ENTHIUM_CAPS
- ENTHIUM + WINMODE → ENTHIUM_WIN

### 8. Enthium-specific combos

| Combo | Positions | Layers | Action | Notes |
|-------|-----------|--------|--------|-------|
| mouse_toggle_e | TBD | ENTHIUM, ENTHIUM_WIN | tog MOUSE | Mirrored position of mouse_toggle_q |
| fatfinger_del_e | 41+42 | ENTHIUM, ENTHIUM_WIN | kp J | Enthium letter at pos 41 |
| fatfinger_bksp_e | 44+43 | ENTHIUM, ENTHIUM_WIN | kp FSLH | Enthium letter at pos 44 |

### 9. Word chords — deferred

Deferred until the user decides to adopt Enthium as daily driver.

### 10. Updates to Gallium and existing layers

The Gallium layer and its conditional layers need updates for:
- Position 54: now `&trans` (inherits base `&lts MOUSE ENTER`)
- Position 57: now `&trans` (inherits base `&kp RGUI`) — the `&enter_mash_proof RGUI ENTER` at position 57 in Gallium layer needs to change to `&trans`

Check all layers that explicitly set position 57 to `&enter_mash_proof RGUI ENTER` and update them.

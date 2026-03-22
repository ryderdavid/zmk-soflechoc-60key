# ZMK Sofle Choc 60-Key — Platform Specification

This is the shared platform specification for the ZMK Sofle Choc 60-key split ergonomic keyboard. It documents the hardware, behavior definitions, HRM strategy, combo architecture, conditional layers, encoders, and display. All layout profiles inherit from this specification.

---

## Hardware Profile

| Property | Value |
|----------|-------|
| Board | `nice_nano@2.0.0` (nRF52840) |
| Shield | `sofle_left` / `sofle_right` |
| Display | nice!view on LEFT half only (via `nice_view_adapter nice_view`); RIGHT half has no display |
| Custom display module | mod-status (`zmk-modules/mod-status/`) — 160x68px landscape, three 68x68 canvases: layer name, BT profiles, battery+WPM. Modifier widget overlays BT area. |
| Keys | 60 (30 per half) |
| Encoders | 2 (EC11, one per half) |
| Connectivity | Bluetooth 5.0 (split wireless) |
| Firmware | ZMK (Zephyr RTOS) |
| ZMK Studio | enabled (`CONFIG_ZMK_STUDIO=y`) |
| Pointing | enabled (`CONFIG_ZMK_POINTING=y`, smooth scrolling) |
| BT name | `SofleChoc60` |
| BT TX power | +8 dBm |
| Sleep | enabled |
| HID indicators | enabled (`CONFIG_ZMK_HID_INDICATORS=y`) |

---

## Physical Layout (60 keys)

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
| 1 (Upper) | 12-23 | 12 | Alpha row |
| 2 (Home) | 24-35 | 12 | Home row |
| 3 (Lower) | 36-49 | 14 | Bottom row + encoder positions 42/43 |
| 4 (Thumb) | 50-59 | 10 | Thumb cluster (5 per hand) |

---

## Layer Architecture (9 layers)

| Index | Define | Display Name | Type | Purpose |
|-------|--------|-------------|------|---------|
| 0 | `QWERTY` | "qwerty" | base | Standard QWERTY with CAGS HRM |
| 1 | `ENGRAM` | "bvhzql" | toggle | Engram BVh ZQl layout with custom shifted pairs via mod-morphs |
| 2 | `ENTHIUM` | "enthium" | toggle | Enthium v14 layout (original orientation) |
| 3 | `NUMBERS` | "numbers" | momentary/toggle | Number grid (left) + numpad (right), symbol row on top |
| 4 | `NAV` | "nav" | momentary | Arrows, page navigation, undo/cut/copy/paste, scroll |
| 5 | `ADJUST` | "adjust" | conditional | Bluetooth, power, Studio unlock, layer toggles (NAV + NUMBERS) |
| 6 | `FKEYS` | "fkeys" | momentary | F1-F12, media controls, BT profile select, Studio unlock |
| 7 | `MOUSE` | "mouse" | momentary/toggle | Mouse movement (fast) on right OHAE cluster, scroll, clicks |
| 8 | `PREC` | "prec" | momentary | Precision mouse — 1/3 speed of fast, accessed from MOUSE layer |

### Layout Cycle

QWERTY -> Engram -> Enthium -> QWERTY (via combo on positions 46+47+48+49). The transition from Engram to Enthium uses the `engram_to_enthium` macro which toggles both layers atomically (`&tog ENGRAM &tog ENTHIUM`).

---

## Custom Behaviors

### Home Row Mods (HRM) — CAGS Order

Strategy: **Ctrl(pinky) Alt(ring) GUI(middle) Shift(index)**, mirrored on right hand. Source: urob/zmk-config anti-misfire pattern.

#### hml / hmr (home_row_mod_left / home_row_mod_right)

| Parameter | Value |
|-----------|-------|
| compatible | `zmk,behavior-hold-tap` |
| flavor | `balanced` |
| tapping-term-ms | 280 |
| quick-tap-ms | 175 (double-tap = two letters) |
| require-prior-idle-ms | 150 (fast typing always taps) |
| hold-trigger-on-release | yes |

**Positional filtering** (hold-trigger-key-positions):

| Behavior | Trigger positions (opposite hand + thumbs) |
|----------|---------------------------------------------|
| hml (left hand) | 6-11, 18-23, 30-35, 43-49, 50-59 |
| hmr (right hand) | 0-5, 12-17, 24-29, 36-42, 50-59 |

#### hml_g / hmr_g (GUI-specific variants)

Same as hml/hmr except:

| Parameter | Value |
|-----------|-------|
| require-prior-idle-ms | 350 (longer idle to prevent accidental Cmd during fast word chords) |

Used on the middle finger (GUI position) in CAGS.

### Layer-Tap Smart (lts)

| Parameter | Value |
|-----------|-------|
| Timing | Same as HRM (280/175/150) |
| Bindings | `<&mo>`, `<&kp>` |
| Positional filtering | None (thumb keys work with both hands) |

### Hold-Tap KP (htk)

| Parameter | Value |
|-----------|-------|
| flavor | balanced |
| tapping-term-ms | 200 |
| quick-tap-ms | 175 |
| Bindings | `<&kp>`, `<&kp>` |
| Usage | Outer thumb keys with Hyper tap actions |

---

## Mod-Morph Behaviors (Engram Custom Shifted Pairs)

Engram uses 18 mod-morph behaviors to implement its non-standard shifted key pairs. When Shift is held, the second binding fires instead of the first.

### Symbol Mod-Morphs (8)

| Name | Base (tap) | Shifted | Used for |
|------|-----------|---------|----------|
| `mm_comma_semi` | `,` | `;` | Engram comma key |
| `mm_dot_colon` | `.` | `:` | Engram period key |
| `mm_sqt_lpar` | `'` | `(` | Engram apostrophe key |
| `mm_dqt_rpar` | `"` | `)` | Engram double-quote key |
| `mm_qmark_excl` | `?` | `!` | Engram question mark key |
| `mm_at_grave` | `@` | `` ` `` | Engram at-sign key |
| `mm_hash_dllr` | `#` | `$` | Engram hash key |
| `mm_fslh_bslh` | `/` | `\` | Engram slash key |

### Number Row Mod-Morphs (10)

Symbol on base tap, number on Shift. Inverts the standard Shift+number=symbol convention.

| Name | Base (tap) | Shifted |
|------|-----------|---------|
| `mm_pipe_n1` | `\|` | `1` |
| `mm_equal_n2` | `=` | `2` |
| `mm_tilde_n3` | `~` | `3` |
| `mm_plus_n4` | `+` | `4` |
| `mm_lt_n5` | `<` | `5` |
| `mm_gt_n6` | `>` | `6` |
| `mm_caret_n7` | `^` | `7` |
| `mm_amps_n8` | `&` | `8` |
| `mm_prcnt_n9` | `%` | `9` |
| `mm_astrk_n0` | `*` | `0` |

---

## Tap Dances

| Name | Tapping Term | Tap 1 | Tap 2 | Purpose |
|------|-------------|-------|-------|---------|
| td_enc_l | 200ms | none | hyper_f | Left encoder press: double = Hyper+F |
| td_enc_r | 200ms | none | meh_f | Right encoder press: double = Meh+F |

---

## Macros

| Name | Action | Notes |
|------|--------|-------|
| hyper | Press all 4 mods (Shift+Ctrl+Alt+GUI), pause for release | Standalone Hyper hold key |
| meh | Press 3 mods (Shift+Ctrl+Alt), pause for release | Standalone Meh hold key |
| hyper_space | Hyper + tap Space | Chord shortcut |
| hyper_f | Hyper + tap F | Left encoder double-tap action |
| meh_f | Meh (Shift+Ctrl+Alt) + tap F | Right encoder double-tap action |
| engram_to_enthium | `&tog ENGRAM &tog ENTHIUM` | Atomic layout switch (wait-ms/tap-ms: 0) |

---

## Combo Architecture

### Escape Combos (always active)

| Name | Positions | Action | Notes |
|------|-----------|--------|-------|
| esc | 25+41 | Escape | A + B (cross-hand) |
| esc2 | 0+12 | Escape | `` ` `` + Tab |
| esc3 | 0+1 | Escape | `` ` `` + 1 |

### Thumb Fat-Finger Protection (always active)

| Name | Positions | Action | Notes |
|------|-----------|--------|-------|
| thumb_fatfinger | 54+55 | Space | Adjacent thumb fat-finger |
| thumb_fatfinger_left | 52+53 | Space | Left thumb fat-finger |
| thumb_fatfinger_right | 56+57 | Space | Right thumb fat-finger |

### Layout Cycle Combos (layer-restricted)

| Name | Positions | Layers | Action | Notes |
|------|-----------|--------|--------|-------|
| layout_to_engram | 46+47+48+49 | QWERTY | tog ENGRAM | QWERTY -> Engram |
| layout_to_enthium | 46+47+48+49 | ENGRAM | engram_to_enthium | Engram -> Enthium (macro) |
| layout_to_qwerty | 46+47+48+49 | ENTHIUM | tog ENTHIUM | Enthium -> QWERTY |

### Toggle Combos

| Name | Positions | Action | Notes |
|------|-----------|--------|-------|
| numbers_toggle | 29+30 | tog NUMBERS | Inner home row (G+H positions) |

### Fat-Finger Encoder Protection (layer-restricted)

| Name | Positions | Layers | Action | Notes |
|------|-----------|--------|--------|-------|
| fatfinger_del_q | 41+42 | QWERTY | kp B | B + encoder = B (not accidental delete) |
| fatfinger_bksp_q | 44+43 | QWERTY | kp N | N + encoder = N |
| fatfinger_del_eng | 41+42 | ENGRAM | kp K | K + encoder = K |
| fatfinger_bksp_eng | 44+43 | ENGRAM | kp R | R + encoder = R |
| fatfinger_del_e | 41+42 | ENTHIUM | kp FSLH | / + encoder = / |
| fatfinger_bksp_e | 44+43 | ENTHIUM | kp J | J + encoder = J |

---

## Conditional Layer Rules

| If Layers | Then Layer | Purpose |
|-----------|------------|---------|
| NAV + NUMBERS | ADJUST | System settings (BT, power, toggles) |

---

## Encoder Configuration

### Physical Keys (Positions 42/43)

| Encoder | Press action |
|---------|-------------|
| Left (pos 42) | `&hyper` (hold = all 4 mods) on QWERTY; `&trans` on Engram/Enthium |
| Right (pos 43) | `&meh` (hold = Shift+Ctrl+Alt) on QWERTY; `&trans` on Engram/Enthium |

### Rotation (sensor-bindings, all layers)

| Encoder | Clockwise | Counter-clockwise |
|---------|-----------|-------------------|
| Left | Volume Up (`C_VOL_UP`) | Volume Down (`C_VOL_DN`) |
| Right | Page Up (`PG_UP`) | Page Down (`PG_DN`) |

---

## Mouse Configuration

| Parameter | Value |
|-----------|-------|
| Fast movement | 195% of ZMK default (1170 vs 600) |
| Slow/precision | 1/3 of fast speed (390) |
| Scroll value | 25 (`ZMK_POINTING_DEFAULT_SCRL_VAL`) |
| Smooth scrolling | enabled |

### Mouse Layer (7) Layout

Right-hand OHAE cluster: scroll up/down flanking move-up, move-left/down/right on home row. Thumb cluster: toggle off, left-click, right-click, middle-click. Left hand provides raw modifiers (Ctrl, Alt, Shift, GUI) for modified clicks.

### Precision Layer (8)

Same layout as Mouse but at 1/3 speed. Activated by holding position 35 (right pinky) while on the Mouse layer.

---

## Build Configuration

Five firmware variants built via GitHub Actions:

| # | Shield | Options |
|---|--------|---------|
| 1 | `sofle_left` + nice_view | Studio + mod-status module |
| 2 | `sofle_right` + nice_view | -- |
| 3 | `sofle_left` (no display) | Studio |
| 4 | `sofle_right` (no display) | -- |
| 5 | settings_reset | -- |

---

## Binding Count Rule

Every layer MUST have exactly **60 bindings**: 12 + 12 + 12 + 14 + 10. Total: 9 layers x 60 bindings = 540 bindings.

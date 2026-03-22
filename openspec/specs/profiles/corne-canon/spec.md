# Profile: Corne-Canon

**Description:** Triple-layout Sofle 60-key configuration with QWERTY, Engram, and Enthium alpha bases sharing common functional layers. CAGS home row mods, Engram mod-morphs for custom shifted pairs, mouse movement with precision mode.

**Based on:** Corne canonical layout (42-key), adapted to Sofle 60-key

**HRM Order:** CAGS (Ctrl-Alt-GUI-Shift, pinky to index)

**Source file:** `config/sofle.keymap`

---

## Layer Architecture

| Index | Define | Display Name | Purpose | Activation |
|-------|--------|-------------|---------|------------|
| 0 | `QWERTY` | qwerty | Main QWERTY base with CAGS HRM | Default |
| 1 | `ENGRAM` | bvhzql | Engram BVh ZQl toggle overlay with mod-morphs | Toggle (layout cycle combo: pos 46+47+48+49) |
| 2 | `ENTHIUM` | enthium | Enthium v14 alpha overlay (original orientation) | Toggle (layout cycle combo: pos 46+47+48+49) |
| 3 | `NUMBERS` | numbers | Number grid + right-side numpad (merged) | Hold (`lts` from pos 0/53/55) or toggle (combo: pos 29+30) |
| 4 | `NAV` | nav | Navigation, arrows, undo/cut/copy/paste | Hold (`mo` from pos 24, `lts` from pos 35/56) |
| 5 | `ADJUST` | adjust | BT, power, layout toggles | Conditional: NAV + NUMBERS |
| 6 | `FKEYS` | fkeys | F1-F12, media, undo/cut/copy/paste column, BT, Studio unlock | Hold (`lts` from pos 59) |
| 7 | `MOUSE` | mouse | Mouse movement (195% speed) | Hold (`lts` from pos 54) or toggle |
| 8 | `PREC` | prec | Precision mouse (1/3 speed, 390 units) | Hold (`mo` from pos 35 on mouse layer) |

---

## Conditional Layer Activation

| Condition | Result Layer |
|-----------|-------------|
| NAV (4) + NUMBERS (3) | ADJUST (5) |

---

## Custom Behaviors

### Home Row Mods

| Behavior | Flavor | Tapping Term | Quick-Tap | Prior Idle | Positional | Notes |
|----------|--------|-------------|-----------|------------|------------|-------|
| `hml` | balanced | 280ms | 175ms | 150ms | Right hand + thumbs | Left-hand HRM |
| `hmr` | balanced | 280ms | 175ms | 150ms | Left hand + thumbs | Right-hand HRM |
| `hml_g` | balanced | 280ms | 175ms | 350ms | Right hand + thumbs | Left GUI (longer idle to prevent Cmd misfires) |
| `hmr_g` | balanced | 280ms | 175ms | 350ms | Left hand + thumbs | Right GUI (longer idle to prevent Cmd misfires) |

### Layer-Tap and Hold-Tap

| Behavior | Type | Tapping Term | Quick-Tap | Prior Idle | Bindings | Notes |
|----------|------|-------------|-----------|------------|----------|-------|
| `lts` | hold-tap | 280ms | 175ms | 150ms | `<&mo>, <&kp>` | Layer-tap with HRM timing |
| `htk` | hold-tap | 200ms | 175ms | -- | `<&kp>, <&kp>` | Hold=modifier, Tap=key (shorter timing for thumbs) |

### Tap Dances

| Behavior | Tapping Term | Tap 1 | Tap 2 | Notes |
|----------|-------------|-------|-------|-------|
| `td_enc_l` | 200ms | `&none` | `&hyper_f` | Left encoder press |
| `td_enc_r` | 200ms | `&none` | `&meh_f` | Right encoder press |

### Macros

| Macro | Output | Notes |
|-------|--------|-------|
| `hyper` | Hold Shift+Ctrl+Alt+GUI | Press-for-release macro |
| `hyper_space` | Hyper+Space | Tap macro |
| `hyper_f` | Hyper+F | Tap macro |
| `meh_f` | Meh+F (Shift+Ctrl+Alt) | Tap macro |
| `meh` | Hold Shift+Ctrl+Alt | Press-for-release macro |
| `engram_to_enthium` | `&tog ENGRAM &tog ENTHIUM` | Layout cycle transition: turns off Engram, turns on Enthium |

### Engram Mod-Morphs (Custom Shifted Pairs)

These mod-morphs replace standard shift behavior for Engram-specific punctuation. Base tap produces one symbol; holding Shift produces a different symbol instead of the standard shifted character.

| Behavior | Base (tap) | Shifted | Notes |
|----------|-----------|---------|-------|
| `mm_comma_semi` | `,` | `;` | |
| `mm_dot_colon` | `.` | `:` | |
| `mm_sqt_lpar` | `'` | `(` | |
| `mm_dqt_rpar` | `"` | `)` | |
| `mm_qmark_excl` | `?` | `!` | |
| `mm_at_grave` | `@` | `` ` `` | |
| `mm_hash_dllr` | `#` | `$` | |
| `mm_fslh_bslh` | `/` | `\` | |

### Engram Number Row Mod-Morphs (Symbol Base, Number on Shift)

| Behavior | Base (tap) | Shifted | Notes |
|----------|-----------|---------|-------|
| `mm_pipe_n1` | `\|` | `1` | |
| `mm_equal_n2` | `=` | `2` | |
| `mm_tilde_n3` | `~` | `3` | |
| `mm_plus_n4` | `+` | `4` | |
| `mm_lt_n5` | `<` | `5` | |
| `mm_gt_n6` | `>` | `6` | |
| `mm_caret_n7` | `^` | `7` | |
| `mm_amps_n8` | `&` | `8` | |
| `mm_prcnt_n9` | `%` | `9` | |
| `mm_astrk_n0` | `*` | `0` | |

---

## Combos

### Utility Combos (always active)

| Name | Positions | Binding | Notes |
|------|-----------|---------|-------|
| esc | 25+41 | `&kp ESCAPE` | A+B positions (home row + bottom row) |
| esc2 | 0+12 | `&kp ESCAPE` | Grave+Tab positions |
| esc3 | 0+1 | `&kp ESCAPE` | Grave+1 positions |
| thumb_fatfinger | 54+55 | `&kp SPACE` | Adjacent inner thumbs |
| thumb_fatfinger_left | 52+53 | `&kp SPACE` | Left thumb fat-finger |
| thumb_fatfinger_right | 56+57 | `&kp SPACE` | Right thumb fat-finger |

### Layout Cycle (QWERTY -> Engram -> Enthium -> QWERTY)

| Name | Positions | Layers | Binding | Notes |
|------|-----------|--------|---------|-------|
| layout_to_engram | 46+47+48+49 | QWERTY (0) | `&tog ENGRAM` | Activates Engram overlay |
| layout_to_enthium | 46+47+48+49 | ENGRAM (1) | `&engram_to_enthium` | Macro: tog off Engram, tog on Enthium |
| layout_to_qwerty | 46+47+48+49 | ENTHIUM (2) | `&tog ENTHIUM` | Deactivates Enthium, returns to QWERTY |

### Numbers Toggle

| Name | Positions | Binding | Notes |
|------|-----------|---------|-------|
| numbers_toggle | 29+30 | `&tog NUMBERS` | G+H positions |

### Fat-Finger Protection (encoder adjacency)

| Name | Positions | Layers | Binding | Notes |
|------|-----------|--------|---------|-------|
| fatfinger_del_q | 41+42 | QWERTY (0) | `&kp B` | B+encoder press outputs B |
| fatfinger_bksp_q | 44+43 | QWERTY (0) | `&kp N` | N+encoder press outputs N |
| fatfinger_del_eng | 41+42 | ENGRAM (1) | `&kp K` | K+encoder press outputs K (Engram pos 41 letter) |
| fatfinger_bksp_eng | 44+43 | ENGRAM (1) | `&kp R` | R+encoder press outputs R (Engram pos 44 letter) |
| fatfinger_del_e | 41+42 | ENTHIUM (2) | `&kp FSLH` | /+encoder press outputs / (Enthium pos 41 key) |
| fatfinger_bksp_e | 44+43 | ENTHIUM (2) | `&kp J` | J+encoder press outputs J (Enthium pos 44 letter) |

---

## Full Binding Tables

### Layer 0: qwerty (Main QWERTY base with CAGS home row mods)

The primary typing layer. Home row mods follow CAGS order (Ctrl-Alt-GUI-Shift) from pinky to index on both hands. Number row is the Sofle-only extension. Thumb cluster provides layer access (Numbers, Nav, Mouse, Fkeys) and system modifiers with Hyper tap actions.

| Pos | Row | Physical Key | Binding | Hold | Tap | Notes |
|-----|-----|-------------|---------|------|-----|-------|
| 0 | 0 | Top-left | `&lts NUMBERS GRAVE` | NUMBERS layer | `` ` `` | Layer-tap |
| 1 | 0 | | `&kp N1` | -- | 1 | |
| 2 | 0 | | `&kp N2` | -- | 2 | |
| 3 | 0 | | `&kp N3` | -- | 3 | |
| 4 | 0 | | `&kp N4` | -- | 4 | |
| 5 | 0 | | `&kp N5` | -- | 5 | |
| 6 | 0 | | `&kp N6` | -- | 6 | |
| 7 | 0 | | `&kp N7` | -- | 7 | |
| 8 | 0 | | `&kp N8` | -- | 8 | |
| 9 | 0 | | `&kp N9` | -- | 9 | |
| 10 | 0 | | `&kp N0` | -- | 0 | |
| 11 | 0 | Top-right | `&kp BSPC` | -- | Backspace | |
| 12 | 1 | | `&kp TAB` | -- | Tab | |
| 13 | 1 | Q | `&kp Q` | -- | Q | |
| 14 | 1 | W | `&kp W` | -- | W | |
| 15 | 1 | E | `&kp E` | -- | E | |
| 16 | 1 | R | `&kp R` | -- | R | |
| 17 | 1 | T | `&kp T` | -- | T | |
| 18 | 1 | Y | `&kp Y` | -- | Y | |
| 19 | 1 | U | `&kp U` | -- | U | |
| 20 | 1 | I | `&kp I` | -- | I | |
| 21 | 1 | O | `&kp O` | -- | O | |
| 22 | 1 | P | `&kp P` | -- | P | |
| 23 | 1 | | `&kp MINUS` | -- | `-` | |
| 24 | 2 | | `&mo NAV` | NAV layer | -- | Momentary only, no tap |
| 25 | 2 | A | `&hml LCTRL A` | Left Ctrl | A | CAGS pinky |
| 26 | 2 | S | `&hml LALT S` | Left Alt | S | CAGS ring |
| 27 | 2 | D | `&hml_g LGUI D` | Left GUI | D | CAGS middle (350ms idle) |
| 28 | 2 | F | `&hml LSHFT F` | Left Shift | F | CAGS index |
| 29 | 2 | G | `&kp G` | -- | G | |
| 30 | 2 | H | `&kp H` | -- | H | |
| 31 | 2 | J | `&hmr RSHFT J` | Right Shift | J | CAGS index |
| 32 | 2 | K | `&hmr_g RGUI K` | Right GUI | K | CAGS middle (350ms idle) |
| 33 | 2 | L | `&hmr RALT L` | Right Alt | L | CAGS ring |
| 34 | 2 | ; | `&hmr RCTRL SEMI` | Right Ctrl | `;` | CAGS pinky |
| 35 | 2 | ' | `&lts NAV SQT` | NAV layer | `'` | Layer-tap |
| 36 | 3 | Left shift | `&kp LSHFT` | -- | Left Shift | |
| 37 | 3 | Z | `&kp Z` | -- | Z | |
| 38 | 3 | X | `&kp X` | -- | X | |
| 39 | 3 | C | `&kp C` | -- | C | |
| 40 | 3 | V | `&kp V` | -- | V | |
| 41 | 3 | B | `&kp B` | -- | B | |
| 42 | 3 | Left encoder | `&hyper` | -- | Hyper (macro) | Press-for-release: Shift+Ctrl+Alt+GUI |
| 43 | 3 | Right encoder | `&meh` | -- | Meh (macro) | Press-for-release: Shift+Ctrl+Alt |
| 44 | 3 | N | `&kp N` | -- | N | |
| 45 | 3 | M | `&kp M` | -- | M | |
| 46 | 3 | , | `&kp COMMA` | -- | `,` | Part of layout cycle combo |
| 47 | 3 | . | `&kp DOT` | -- | `.` | Part of layout cycle combo |
| 48 | 3 | / | `&kp FSLH` | -- | `/` | Part of layout cycle combo |
| 49 | 3 | Right shift | `&mt RSHFT FSLH` | Right Shift | `/` | Mod-tap; part of layout cycle combo |
| 50 | 4 | Left outer 1 | `&htk LCTRL LS(LC(LA(LG(Z))))` | Left Ctrl | Hyper+Z | |
| 51 | 4 | Left outer 2 | `&htk LALT LS(LC(LA(LG(B))))` | Left Alt | Hyper+B | |
| 52 | 4 | Left inner 1 | `&htk LGUI LS(LC(LA(LG(A))))` | Left GUI | Hyper+A | |
| 53 | 4 | Left inner 2 | `&lts NUMBERS ESC` | NUMBERS layer | Escape | Layer-tap |
| 54 | 4 | Left inner 3 | `&lts MOUSE ENTER` | MOUSE layer | Enter | Layer-tap |
| 55 | 4 | Right inner 3 | `&lts NUMBERS SPACE` | NUMBERS layer | Space | Layer-tap |
| 56 | 4 | Right inner 2 | `&lts NAV SPACE` | NAV layer | Space | Layer-tap |
| 57 | 4 | Right inner 1 | `&kp RGUI` | -- | Right GUI | Dedicated modifier |
| 58 | 4 | Right outer 2 | `&htk RALT LS(LC(LA(LG(Y))))` | Right Alt | Hyper+Y | |
| 59 | 4 | Right outer 1 | `&lts FKEYS ENTER` | FKEYS layer | Enter | Layer-tap |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 1: bvhzql (Engram BVh ZQl toggle overlay)

Toggle overlay that replaces all keys with Engram-specific bindings. Unlike a simple alpha remap, this layer uses mod-morphs extensively: the number row produces symbols by default and numbers when shifted (inverted from QWERTY), and punctuation keys produce custom shifted pairs (e.g., `,` -> `;` on shift, `'` -> `(` on shift). The home row uses the same CAGS HRM order with Engram letters. Position 24 changes to `&lts NAV B` (layer-tap: hold=Nav, tap=B). Position 35 changes to `&lts NAV V`. The `&none` at position 13 is intentional (Engram has no key there). Thumb row is mostly `&trans` except positions 55, 57, and 58 which provide Engram-specific symbols.

| Pos | Row | Physical Key | Binding | Hold | Tap | Notes |
|-----|-----|-------------|---------|------|-----|-------|
| 0 | 0 | | `&mm_at_grave` | -- | `@` / Shift: `` ` `` | Mod-morph |
| 1 | 0 | | `&mm_pipe_n1` | -- | `\|` / Shift: `1` | Mod-morph |
| 2 | 0 | | `&mm_equal_n2` | -- | `=` / Shift: `2` | Mod-morph |
| 3 | 0 | | `&mm_tilde_n3` | -- | `~` / Shift: `3` | Mod-morph |
| 4 | 0 | | `&mm_plus_n4` | -- | `+` / Shift: `4` | Mod-morph |
| 5 | 0 | | `&mm_lt_n5` | -- | `<` / Shift: `5` | Mod-morph |
| 6 | 0 | | `&mm_gt_n6` | -- | `>` / Shift: `6` | Mod-morph |
| 7 | 0 | | `&mm_caret_n7` | -- | `^` / Shift: `7` | Mod-morph |
| 8 | 0 | | `&mm_amps_n8` | -- | `&` / Shift: `8` | Mod-morph |
| 9 | 0 | | `&mm_prcnt_n9` | -- | `%` / Shift: `9` | Mod-morph |
| 10 | 0 | | `&mm_astrk_n0` | -- | `*` / Shift: `0` | Mod-morph |
| 11 | 0 | | `&kp BSPC` | -- | Backspace | |
| 12 | 1 | | `&kp TAB` | -- | Tab | |
| 13 | 1 | | `&none` | -- | -- | Disabled (no Engram key here) |
| 14 | 1 | | `&kp Y` | -- | Y | |
| 15 | 1 | | `&kp O` | -- | O | |
| 16 | 1 | | `&kp U` | -- | U | |
| 17 | 1 | | `&mm_sqt_lpar` | -- | `'` / Shift: `(` | Mod-morph |
| 18 | 1 | | `&mm_dqt_rpar` | -- | `"` / Shift: `)` | Mod-morph |
| 19 | 1 | | `&kp L` | -- | L | |
| 20 | 1 | | `&kp D` | -- | D | |
| 21 | 1 | | `&kp W` | -- | W | |
| 22 | 1 | | `&kp LBKT` | -- | `[` | |
| 23 | 1 | | `&kp RBKT` | -- | `]` | |
| 24 | 2 | | `&lts NAV B` | NAV layer | B | Layer-tap |
| 25 | 2 | | `&hml LCTRL C` | Left Ctrl | C | CAGS pinky |
| 26 | 2 | | `&hml LALT I` | Left Alt | I | CAGS ring |
| 27 | 2 | | `&hml_g LGUI E` | Left GUI | E | CAGS middle (350ms idle) |
| 28 | 2 | | `&hml LSHFT A` | Left Shift | A | CAGS index |
| 29 | 2 | | `&mm_comma_semi` | -- | `,` / Shift: `;` | Mod-morph |
| 30 | 2 | | `&mm_dot_colon` | -- | `.` / Shift: `:` | Mod-morph |
| 31 | 2 | | `&hmr RSHFT H` | Right Shift | H | CAGS index |
| 32 | 2 | | `&hmr_g RGUI T` | Right GUI | T | CAGS middle (350ms idle) |
| 33 | 2 | | `&hmr RALT S` | Right Alt | S | CAGS ring |
| 34 | 2 | | `&hmr RCTRL N` | Right Ctrl | N | CAGS pinky |
| 35 | 2 | | `&lts NAV V` | NAV layer | V | Layer-tap |
| 36 | 3 | | `&mt LSHFT Z` | Left Shift | Z | Mod-tap |
| 37 | 3 | | `&kp G` | -- | G | |
| 38 | 3 | | `&kp X` | -- | X | |
| 39 | 3 | | `&kp J` | -- | J | |
| 40 | 3 | | `&kp K` | -- | K | |
| 41 | 3 | | `&kp MINUS` | -- | `-` | |
| 42 | 3 | Left encoder | `&trans` | -- | -- | Inherits Hyper from QWERTY |
| 43 | 3 | Right encoder | `&trans` | -- | -- | Inherits Meh from QWERTY |
| 44 | 3 | | `&mm_qmark_excl` | -- | `?` / Shift: `!` | Mod-morph |
| 45 | 3 | | `&kp R` | -- | R | |
| 46 | 3 | | `&kp M` | -- | M | |
| 47 | 3 | | `&kp F` | -- | F | |
| 48 | 3 | | `&kp P` | -- | P | |
| 49 | 3 | | `&mt RSHFT Q` | Right Shift | Q | Mod-tap |
| 50 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 51 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 52 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 53 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 54 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 55 | 4 | | `&lts NUMBERS SPACE` | NUMBERS layer | Space | Explicit (same as QWERTY) |
| 56 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 57 | 4 | | `&mm_hash_dllr` | -- | `#` / Shift: `$` | Mod-morph (replaces RGUI) |
| 58 | 4 | | `&mm_fslh_bslh` | -- | `/` / Shift: `\` | Mod-morph (replaces Hyper+Y) |
| 59 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 2: enthium (Enthium v14 toggle overlay, original orientation)

Toggle overlay that replaces alpha and punctuation keys with Enthium v14 positions. Most of the number row and thumb cluster inherit from layer 0 via `&trans`. Home row uses the same CAGS HRM order with Enthium letters. Position 24 changes to `&lts NAV B`. Position 35 changes to `&lts NAV W`. Position 41 adds mouse layer access via `&lts MOUSE FSLH`. The thumb row diverges significantly from QWERTY: position 53 changes to `&lts NUMBERS SPACE` and position 55 to `&lts NUMBERS R`, reflecting Enthium's thumb-R design.

| Pos | Row | Physical Key | Binding | Hold | Tap | Notes |
|-----|-----|-------------|---------|------|-----|-------|
| 0 | 0 | | `&trans` | -- | -- | Inherits `&lts NUMBERS GRAVE` from QWERTY |
| 1 | 0 | | `&trans` | -- | -- | Inherits 1 |
| 2 | 0 | | `&trans` | -- | -- | Inherits 2 |
| 3 | 0 | | `&trans` | -- | -- | Inherits 3 |
| 4 | 0 | | `&trans` | -- | -- | Inherits 4 |
| 5 | 0 | | `&trans` | -- | -- | Inherits 5 |
| 6 | 0 | | `&trans` | -- | -- | Inherits 6 |
| 7 | 0 | | `&trans` | -- | -- | Inherits 7 |
| 8 | 0 | | `&trans` | -- | -- | Inherits 8 |
| 9 | 0 | | `&trans` | -- | -- | Inherits 9 |
| 10 | 0 | | `&trans` | -- | -- | Inherits 0 |
| 11 | 0 | | `&trans` | -- | -- | Inherits Backspace |
| 12 | 1 | | `&trans` | -- | -- | Inherits Tab |
| 13 | 1 | | `&kp Q` | -- | Q | |
| 14 | 1 | | `&kp Y` | -- | Y | |
| 15 | 1 | | `&kp O` | -- | O | |
| 16 | 1 | | `&kp U` | -- | U | |
| 17 | 1 | | `&kp EQUAL` | -- | `=` | |
| 18 | 1 | | `&kp X` | -- | X | |
| 19 | 1 | | `&kp L` | -- | L | |
| 20 | 1 | | `&kp D` | -- | D | |
| 21 | 1 | | `&kp P` | -- | P | |
| 22 | 1 | | `&kp Z` | -- | Z | |
| 23 | 1 | | `&trans` | -- | -- | Inherits `-` from QWERTY |
| 24 | 2 | | `&lts NAV B` | NAV layer | B | Layer-tap |
| 25 | 2 | | `&hml LCTRL C` | Left Ctrl | C | CAGS pinky |
| 26 | 2 | | `&hml LALT I` | Left Alt | I | CAGS ring |
| 27 | 2 | | `&hml_g LGUI A` | Left GUI | A | CAGS middle (350ms idle) |
| 28 | 2 | | `&hml LSHFT E` | Left Shift | E | CAGS index |
| 29 | 2 | | `&kp MINUS` | -- | `-` | |
| 30 | 2 | | `&kp K` | -- | K | |
| 31 | 2 | | `&hmr RSHFT H` | Right Shift | H | CAGS index |
| 32 | 2 | | `&hmr_g RGUI T` | Right GUI | T | CAGS middle (350ms idle) |
| 33 | 2 | | `&hmr RALT N` | Right Alt | N | CAGS ring |
| 34 | 2 | | `&hmr RCTRL S` | Right Ctrl | S | CAGS pinky |
| 35 | 2 | | `&lts NAV W` | NAV layer | W | Layer-tap |
| 36 | 3 | | `&mt LSHFT EXCL` | Left Shift | `!` | Mod-tap |
| 37 | 3 | | `&kp SQT` | -- | `'` | |
| 38 | 3 | | `&kp COMMA` | -- | `,` | |
| 39 | 3 | | `&kp DOT` | -- | `.` | |
| 40 | 3 | | `&kp SEMI` | -- | `;` | |
| 41 | 3 | | `&lts MOUSE FSLH` | MOUSE layer | `/` | Layer-tap |
| 42 | 3 | Left encoder | `&trans` | -- | -- | Inherits Hyper from QWERTY |
| 43 | 3 | Right encoder | `&trans` | -- | -- | Inherits Meh from QWERTY |
| 44 | 3 | | `&kp J` | -- | J | |
| 45 | 3 | | `&kp M` | -- | M | |
| 46 | 3 | | `&kp G` | -- | G | |
| 47 | 3 | | `&kp F` | -- | F | |
| 48 | 3 | | `&kp V` | -- | V | |
| 49 | 3 | | `&mt RSHFT EXCL` | Right Shift | `!` | Mod-tap |
| 50 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 51 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 52 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 53 | 4 | | `&lts NUMBERS SPACE` | NUMBERS layer | Space | Replaces QWERTY's `&lts NUMBERS ESC` |
| 54 | 4 | | `&trans` | -- | -- | Inherits `&lts MOUSE ENTER` from QWERTY |
| 55 | 4 | | `&lts NUMBERS R` | NUMBERS layer | R | Enthium thumb-R; replaces QWERTY's `&lts NUMBERS SPACE` |
| 56 | 4 | | `&lts NAV SPACE` | NAV layer | Space | Explicit (same as QWERTY) |
| 57 | 4 | | `&trans` | -- | -- | Inherits RGUI |
| 58 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |
| 59 | 4 | | `&trans` | -- | -- | Inherits from QWERTY |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 3: numbers (Number grid + right-side numpad, merged)

Activated by holding pos 0/53/55 (`lts NUMBERS`) or toggled via combo (pos 29+30). Left side provides a sequential number layout (1-0) across Rows 1-2, with shifted symbols (`!@#$%`) on Row 0 and more shifted symbols (`^&*()`) on Row 3. Right side provides a calculator-style numpad grid with operators. Kept from the Corne layout despite the Sofle having a physical number row, for muscle memory.

| Pos | Row | Physical Key | Binding | Notes |
|-----|-----|-------------|---------|-------|
| 0 | 0 | | `&trans` | Inherits `&lts NUMBERS GRAVE` |
| 1 | 0 | | `&kp EXCL` | `!` |
| 2 | 0 | | `&kp AT` | `@` |
| 3 | 0 | | `&kp HASH` | `#` |
| 4 | 0 | | `&kp DLLR` | `$` |
| 5 | 0 | | `&kp PRCNT` | `%` |
| 6 | 0 | | `&trans` | |
| 7 | 0 | | `&trans` | |
| 8 | 0 | | `&trans` | |
| 9 | 0 | | `&trans` | |
| 10 | 0 | | `&trans` | |
| 11 | 0 | | `&trans` | |
| 12 | 1 | | `&kp GRAVE` | `` ` `` |
| 13 | 1 | | `&kp N1` | 1 |
| 14 | 1 | | `&kp N2` | 2 |
| 15 | 1 | | `&kp N3` | 3 |
| 16 | 1 | | `&kp N4` | 4 |
| 17 | 1 | | `&kp N5` | 5 |
| 18 | 1 | | `&kp ASTRK` | `*` (numpad operator) |
| 19 | 1 | | `&kp N7` | 7 (numpad) |
| 20 | 1 | | `&kp N8` | 8 (numpad) |
| 21 | 1 | | `&kp N9` | 9 (numpad) |
| 22 | 1 | | `&trans` | |
| 23 | 1 | | `&trans` | |
| 24 | 2 | | `&none` | Disabled |
| 25 | 2 | | `&kp N6` | 6 |
| 26 | 2 | | `&kp N7` | 7 |
| 27 | 2 | | `&kp N8` | 8 |
| 28 | 2 | | `&kp N9` | 9 |
| 29 | 2 | | `&kp N0` | 0 |
| 30 | 2 | | `&kp MINUS` | `-` (numpad operator) |
| 31 | 2 | | `&kp N4` | 4 (numpad) |
| 32 | 2 | | `&kp N5` | 5 (numpad) |
| 33 | 2 | | `&kp N6` | 6 (numpad) |
| 34 | 2 | | `&trans` | |
| 35 | 2 | | `&trans` | |
| 36 | 3 | | `&trans` | Inherits Shift |
| 37 | 3 | | `&kp CARET` | `^` |
| 38 | 3 | | `&kp AMPS` | `&` |
| 39 | 3 | | `&kp ASTRK` | `*` |
| 40 | 3 | | `&kp LPAR` | `(` |
| 41 | 3 | | `&kp RPAR` | `)` |
| 42 | 3 | Left encoder | `&trans` | Inherits Hyper |
| 43 | 3 | Right encoder | `&trans` | Inherits Meh |
| 44 | 3 | | `&kp PLUS` | `+` (numpad operator) |
| 45 | 3 | | `&kp N1` | 1 (numpad) |
| 46 | 3 | | `&kp N2` | 2 (numpad) |
| 47 | 3 | | `&kp N3` | 3 (numpad) |
| 48 | 3 | | `&trans` | |
| 49 | 3 | | `&trans` | |
| 50 | 4 | | `&trans` | Inherits from QWERTY |
| 51 | 4 | | `&trans` | Inherits from QWERTY |
| 52 | 4 | | `&trans` | Inherits from QWERTY |
| 53 | 4 | | `&trans` | Inherits from QWERTY |
| 54 | 4 | | `&trans` | Inherits from QWERTY |
| 55 | 4 | | `&kp ENTER` | Enter (numpad) |
| 56 | 4 | | `&kp SPACE` | Space |
| 57 | 4 | | `&kp N0` | 0 (numpad) |
| 58 | 4 | | `&kp DOT` | `.` (numpad decimal) |
| 59 | 4 | | `&kp ENTER` | Enter (numpad) |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 4: nav (Navigation, arrows, undo/cut/copy/paste)

Left hand provides undo/cut/copy/paste on Row 3 (Cmd+Z/X/C/V). Left Rows 0-2 are transparent, preserving modifiers. Right hand provides arrow keys on the home row, PgUp/PgDn and Up on Row 1, Home/End on Row 2/3, scroll wheel, and browser back/forward. Position 11 becomes Delete.

| Pos | Row | Physical Key | Binding | Notes |
|-----|-----|-------------|---------|-------|
| 0 | 0 | | `&trans` | |
| 1 | 0 | | `&trans` | |
| 2 | 0 | | `&trans` | |
| 3 | 0 | | `&trans` | |
| 4 | 0 | | `&trans` | |
| 5 | 0 | | `&trans` | |
| 6 | 0 | | `&trans` | |
| 7 | 0 | | `&trans` | |
| 8 | 0 | | `&trans` | |
| 9 | 0 | | `&trans` | |
| 10 | 0 | | `&trans` | |
| 11 | 0 | | `&kp DELETE` | Delete |
| 12 | 1 | | `&trans` | |
| 13 | 1 | | `&trans` | |
| 14 | 1 | | `&trans` | |
| 15 | 1 | | `&trans` | |
| 16 | 1 | | `&trans` | |
| 17 | 1 | | `&trans` | |
| 18 | 1 | | `&none` | Disabled |
| 19 | 1 | | `&kp PG_UP` | Page Up |
| 20 | 1 | | `&kp UP` | Up Arrow |
| 21 | 1 | | `&kp PG_DN` | Page Down |
| 22 | 1 | | `&kp LG(LBKT)` | Browser Back (Cmd+[) |
| 23 | 1 | | `&kp LG(RBKT)` | Browser Forward (Cmd+]) |
| 24 | 2 | | `&trans` | |
| 25 | 2 | | `&trans` | |
| 26 | 2 | | `&trans` | |
| 27 | 2 | | `&trans` | |
| 28 | 2 | | `&trans` | |
| 29 | 2 | | `&trans` | |
| 30 | 2 | | `&kp HOME` | Home |
| 31 | 2 | | `&kp LEFT` | Left Arrow |
| 32 | 2 | | `&kp DOWN` | Down Arrow |
| 33 | 2 | | `&kp RIGHT` | Right Arrow |
| 34 | 2 | | `&none` | Disabled |
| 35 | 2 | | `&trans` | |
| 36 | 3 | | `&trans` | Inherits Shift |
| 37 | 3 | | `&kp LG(Z)` | Undo (Cmd+Z) |
| 38 | 3 | | `&kp LG(X)` | Cut (Cmd+X) |
| 39 | 3 | | `&kp LG(C)` | Copy (Cmd+C) |
| 40 | 3 | | `&kp LG(V)` | Paste (Cmd+V) |
| 41 | 3 | | `&none` | Disabled |
| 42 | 3 | Left encoder | `&trans` | |
| 43 | 3 | Right encoder | `&trans` | |
| 44 | 3 | | `&kp END` | End |
| 45 | 3 | | `&msc SCRL_UP` | Scroll Up |
| 46 | 3 | | `&none` | Disabled |
| 47 | 3 | | `&msc SCRL_DOWN` | Scroll Down |
| 48 | 3 | | `&none` | Disabled |
| 49 | 3 | | `&none` | Disabled |
| 50 | 4 | | `&trans` | |
| 51 | 4 | | `&trans` | |
| 52 | 4 | | `&trans` | |
| 53 | 4 | | `&trans` | |
| 54 | 4 | | `&trans` | |
| 55 | 4 | | `&none` | Disabled |
| 56 | 4 | | `&trans` | |
| 57 | 4 | | `&trans` | |
| 58 | 4 | | `&trans` | |
| 59 | 4 | | `&trans` | |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 5: adjust (BT, power, system settings -- conditional: NAV + NUMBERS)

Conditional layer activated when both NAV and NUMBERS are held simultaneously. Provides Bluetooth profile management, external power toggle, ZMK Studio unlock, and layout toggles (Engram, Enthium, Mouse).

| Pos | Row | Physical Key | Binding | Notes |
|-----|-----|-------------|---------|-------|
| 0 | 0 | | `&bt BT_CLR_ALL` | Clear all BT profiles |
| 1 | 0 | | `&bt BT_SEL 0` | Select BT profile 0 |
| 2 | 0 | | `&bt BT_SEL 1` | Select BT profile 1 |
| 3 | 0 | | `&bt BT_SEL 2` | Select BT profile 2 |
| 4 | 0 | | `&bt BT_SEL 3` | Select BT profile 3 |
| 5 | 0 | | `&bt BT_SEL 4` | Select BT profile 4 |
| 6 | 0 | | `&bt BT_CLR` | Clear current BT profile |
| 7 | 0 | | `&none` | Disabled |
| 8 | 0 | | `&none` | Disabled |
| 9 | 0 | | `&none` | Disabled |
| 10 | 0 | | `&none` | Disabled |
| 11 | 0 | | `&none` | Disabled |
| 12 | 1 | | `&ext_power EP_TOG` | Toggle external power |
| 13 | 1 | | `&none` | Disabled |
| 14 | 1 | | `&none` | Disabled |
| 15 | 1 | | `&none` | Disabled |
| 16 | 1 | | `&none` | Disabled |
| 17 | 1 | | `&studio_unlock` | ZMK Studio unlock |
| 18 | 1 | | `&none` | Disabled |
| 19 | 1 | | `&none` | Disabled |
| 20 | 1 | | `&none` | Disabled |
| 21 | 1 | | `&none` | Disabled |
| 22 | 1 | | `&none` | Disabled |
| 23 | 1 | | `&none` | Disabled |
| 24 | 2 | | `&none` | Disabled |
| 25 | 2 | | `&none` | Disabled |
| 26 | 2 | | `&none` | Disabled |
| 27 | 2 | | `&none` | Disabled |
| 28 | 2 | | `&none` | Disabled |
| 29 | 2 | | `&tog ENGRAM` | Toggle Engram layout |
| 30 | 2 | | `&tog ENTHIUM` | Toggle Enthium layout |
| 31 | 2 | | `&tog MOUSE` | Toggle Mouse layer |
| 32 | 2 | | `&none` | Disabled |
| 33 | 2 | | `&none` | Disabled |
| 34 | 2 | | `&none` | Disabled |
| 35 | 2 | | `&none` | Disabled |
| 36 | 3 | | `&none` | Disabled |
| 37 | 3 | | `&none` | Disabled |
| 38 | 3 | | `&none` | Disabled |
| 39 | 3 | | `&none` | Disabled |
| 40 | 3 | | `&none` | Disabled |
| 41 | 3 | | `&none` | Disabled |
| 42 | 3 | Left encoder | `&none` | Disabled |
| 43 | 3 | Right encoder | `&none` | Disabled |
| 44 | 3 | | `&none` | Disabled |
| 45 | 3 | | `&none` | Disabled |
| 46 | 3 | | `&none` | Disabled |
| 47 | 3 | | `&none` | Disabled |
| 48 | 3 | | `&none` | Disabled |
| 49 | 3 | | `&none` | Disabled |
| 50 | 4 | | `&none` | Disabled |
| 51 | 4 | | `&none` | Disabled |
| 52 | 4 | | `&none` | Disabled |
| 53 | 4 | | `&none` | Disabled |
| 54 | 4 | | `&none` | Disabled |
| 55 | 4 | | `&none` | Disabled |
| 56 | 4 | | `&none` | Disabled |
| 57 | 4 | | `&none` | Disabled |
| 58 | 4 | | `&none` | Disabled |
| 59 | 4 | | `&none` | Disabled |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 6: fkeys (F1-F12, media, undo/cut/copy/paste column, BT, Studio unlock)

Activated by holding pos 59 (right outer thumb). Left column (pos 0/12/24/36) provides an undo/cut/copy/paste vertical stack. F-keys are arranged: F1-F5 on Row 0, F6-F10 on Row 1, F11-F12 on Row 2. Right side provides media controls (Mute, Volume) on the right edge. Bottom row includes BT profile selection and Studio unlock on the left outer thumb.

| Pos | Row | Physical Key | Binding | Notes |
|-----|-----|-------------|---------|-------|
| 0 | 0 | | `&kp LG(Z)` | Undo (Cmd+Z) |
| 1 | 0 | | `&kp F1` | F1 |
| 2 | 0 | | `&kp F2` | F2 |
| 3 | 0 | | `&kp F3` | F3 |
| 4 | 0 | | `&kp F4` | F4 |
| 5 | 0 | | `&kp F5` | F5 |
| 6 | 0 | | `&trans` | |
| 7 | 0 | | `&trans` | |
| 8 | 0 | | `&trans` | |
| 9 | 0 | | `&trans` | |
| 10 | 0 | | `&trans` | |
| 11 | 0 | | `&trans` | |
| 12 | 1 | | `&kp LG(X)` | Cut (Cmd+X) |
| 13 | 1 | | `&kp F6` | F6 |
| 14 | 1 | | `&kp F7` | F7 |
| 15 | 1 | | `&kp F8` | F8 |
| 16 | 1 | | `&kp F9` | F9 |
| 17 | 1 | | `&kp F10` | F10 |
| 18 | 1 | | `&trans` | |
| 19 | 1 | | `&trans` | |
| 20 | 1 | | `&trans` | |
| 21 | 1 | | `&trans` | |
| 22 | 1 | | `&trans` | |
| 23 | 1 | | `&kp C_MUTE` | Mute |
| 24 | 2 | | `&kp LG(C)` | Copy (Cmd+C) |
| 25 | 2 | | `&kp F11` | F11 |
| 26 | 2 | | `&kp F12` | F12 |
| 27 | 2 | | `&trans` | |
| 28 | 2 | | `&trans` | |
| 29 | 2 | | `&trans` | |
| 30 | 2 | | `&trans` | |
| 31 | 2 | | `&trans` | |
| 32 | 2 | | `&trans` | |
| 33 | 2 | | `&trans` | |
| 34 | 2 | | `&trans` | |
| 35 | 2 | | `&kp C_VOL_UP` | Volume Up |
| 36 | 3 | | `&kp LG(V)` | Paste (Cmd+V) |
| 37 | 3 | | `&bt BT_SEL 0` | Select BT profile 0 |
| 38 | 3 | | `&bt BT_SEL 1` | Select BT profile 1 |
| 39 | 3 | | `&bt BT_SEL 2` | Select BT profile 2 |
| 40 | 3 | | `&bt BT_SEL 3` | Select BT profile 3 |
| 41 | 3 | | `&bt BT_SEL 4` | Select BT profile 4 |
| 42 | 3 | Left encoder | `&trans` | |
| 43 | 3 | Right encoder | `&trans` | |
| 44 | 3 | | `&trans` | |
| 45 | 3 | | `&trans` | |
| 46 | 3 | | `&trans` | |
| 47 | 3 | | `&trans` | |
| 48 | 3 | | `&trans` | |
| 49 | 3 | | `&kp C_VOL_DN` | Volume Down |
| 50 | 4 | | `&studio_unlock` | ZMK Studio unlock |
| 51 | 4 | | `&trans` | |
| 52 | 4 | | `&trans` | |
| 53 | 4 | | `&trans` | |
| 54 | 4 | | `&trans` | |
| 55 | 4 | | `&trans` | |
| 56 | 4 | | `&trans` | |
| 57 | 4 | | `&trans` | |
| 58 | 4 | | `&trans` | |
| 59 | 4 | | `&trans` | |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 7: mouse (Mouse movement on right hand)

Right-hand OHAE cluster (positions 19-20-21 upper, 31-32-33 home) provides mouse movement at 195% of ZMK default speed (1170 units). Scroll wheel on positions 19/21 (upper row flanking the up-movement key). Left hand provides bare modifiers in CAGS order for click-modified actions. Precision mode available via pinky hold at pos 35. Toggle exit via pos 42/43 encoder presses and pos 55. Also accessible via `lts MOUSE` at pos 54 (left inner thumb) or pos 41 (Enthium `/` key).

| Pos | Row | Physical Key | Binding | Notes |
|-----|-----|-------------|---------|-------|
| 0 | 0 | | `&none` | Disabled |
| 1 | 0 | | `&none` | Disabled |
| 2 | 0 | | `&none` | Disabled |
| 3 | 0 | | `&none` | Disabled |
| 4 | 0 | | `&none` | Disabled |
| 5 | 0 | | `&none` | Disabled |
| 6 | 0 | | `&none` | Disabled |
| 7 | 0 | | `&none` | Disabled |
| 8 | 0 | | `&none` | Disabled |
| 9 | 0 | | `&none` | Disabled |
| 10 | 0 | | `&none` | Disabled |
| 11 | 0 | | `&none` | Disabled |
| 12 | 1 | | `&none` | Disabled |
| 13 | 1 | | `&none` | Disabled |
| 14 | 1 | | `&none` | Disabled |
| 15 | 1 | | `&none` | Disabled |
| 16 | 1 | | `&none` | Disabled |
| 17 | 1 | | `&none` | Disabled |
| 18 | 1 | | `&none` | Disabled |
| 19 | 1 | | `&msc SCRL_UP` | Scroll Up |
| 20 | 1 | | `&mmv MOVE_UP_FAST` | Mouse Up (1170 units) |
| 21 | 1 | | `&msc SCRL_DOWN` | Scroll Down |
| 22 | 1 | | `&none` | Disabled |
| 23 | 1 | | `&none` | Disabled |
| 24 | 2 | | `&none` | Disabled |
| 25 | 2 | | `&kp LCTRL` | Left Ctrl (bare modifier) |
| 26 | 2 | | `&kp LALT` | Left Alt (bare modifier) |
| 27 | 2 | | `&kp LSHFT` | Left Shift (bare modifier) |
| 28 | 2 | | `&kp LGUI` | Left GUI (bare modifier) |
| 29 | 2 | | `&none` | Disabled |
| 30 | 2 | | `&none` | Disabled |
| 31 | 2 | | `&mmv MOVE_LEFT_FAST` | Mouse Left (1170 units) |
| 32 | 2 | | `&mmv MOVE_DOWN_FAST` | Mouse Down (1170 units) |
| 33 | 2 | | `&mmv MOVE_RIGHT_FAST` | Mouse Right (1170 units) |
| 34 | 2 | | `&none` | Disabled |
| 35 | 2 | | `&mo PREC` | Hold for precision mode |
| 36 | 3 | | `&none` | Disabled |
| 37 | 3 | | `&none` | Disabled |
| 38 | 3 | | `&none` | Disabled |
| 39 | 3 | | `&none` | Disabled |
| 40 | 3 | | `&none` | Disabled |
| 41 | 3 | | `&none` | Disabled |
| 42 | 3 | Left encoder | `&tog MOUSE` | Toggle mouse off |
| 43 | 3 | Right encoder | `&tog MOUSE` | Toggle mouse off |
| 44 | 3 | | `&none` | Disabled |
| 45 | 3 | | `&none` | Disabled |
| 46 | 3 | | `&none` | Disabled |
| 47 | 3 | | `&none` | Disabled |
| 48 | 3 | | `&none` | Disabled |
| 49 | 3 | | `&none` | Disabled |
| 50 | 4 | | `&none` | Disabled |
| 51 | 4 | | `&none` | Disabled |
| 52 | 4 | | `&none` | Disabled |
| 53 | 4 | | `&none` | Disabled |
| 54 | 4 | | `&none` | Disabled |
| 55 | 4 | | `&tog MOUSE` | Toggle mouse off |
| 56 | 4 | | `&mkp LCLK` | Left Click |
| 57 | 4 | | `&mkp RCLK` | Right Click |
| 58 | 4 | | `&mkp MCLK` | Middle Click |
| 59 | 4 | | `&none` | Disabled |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

### Layer 8: prec (Precision mouse at 1/3 speed)

Activated by holding pos 35 (right pinky) while on the mouse layer. Identical layout to mouse layer but with movement speed reduced to 1/3 (390 units vs 1170). Allows fine-grained cursor positioning for small targets. Uses `&trans` at pos 43 and 55 to inherit toggle-off from mouse layer. Encoder left (42) and pos 35 are `&none` since they are the activating keys or not needed.

| Pos | Row | Physical Key | Binding | Notes |
|-----|-----|-------------|---------|-------|
| 0 | 0 | | `&none` | Disabled |
| 1 | 0 | | `&none` | Disabled |
| 2 | 0 | | `&none` | Disabled |
| 3 | 0 | | `&none` | Disabled |
| 4 | 0 | | `&none` | Disabled |
| 5 | 0 | | `&none` | Disabled |
| 6 | 0 | | `&none` | Disabled |
| 7 | 0 | | `&none` | Disabled |
| 8 | 0 | | `&none` | Disabled |
| 9 | 0 | | `&none` | Disabled |
| 10 | 0 | | `&none` | Disabled |
| 11 | 0 | | `&none` | Disabled |
| 12 | 1 | | `&none` | Disabled |
| 13 | 1 | | `&none` | Disabled |
| 14 | 1 | | `&none` | Disabled |
| 15 | 1 | | `&none` | Disabled |
| 16 | 1 | | `&none` | Disabled |
| 17 | 1 | | `&none` | Disabled |
| 18 | 1 | | `&none` | Disabled |
| 19 | 1 | | `&msc SCRL_UP` | Scroll Up |
| 20 | 1 | | `&mmv MOVE_UP_SLOW` | Mouse Up (390 units) |
| 21 | 1 | | `&msc SCRL_DOWN` | Scroll Down |
| 22 | 1 | | `&none` | Disabled |
| 23 | 1 | | `&none` | Disabled |
| 24 | 2 | | `&none` | Disabled |
| 25 | 2 | | `&kp LCTRL` | Left Ctrl (bare modifier) |
| 26 | 2 | | `&kp LALT` | Left Alt (bare modifier) |
| 27 | 2 | | `&kp LSHFT` | Left Shift (bare modifier) |
| 28 | 2 | | `&kp LGUI` | Left GUI (bare modifier) |
| 29 | 2 | | `&none` | Disabled |
| 30 | 2 | | `&none` | Disabled |
| 31 | 2 | | `&mmv MOVE_LEFT_SLOW` | Mouse Left (390 units) |
| 32 | 2 | | `&mmv MOVE_DOWN_SLOW` | Mouse Down (390 units) |
| 33 | 2 | | `&mmv MOVE_RIGHT_SLOW` | Mouse Right (390 units) |
| 34 | 2 | | `&none` | Disabled |
| 35 | 2 | | `&none` | Disabled (this is the activating key) |
| 36 | 3 | | `&none` | Disabled |
| 37 | 3 | | `&none` | Disabled |
| 38 | 3 | | `&none` | Disabled |
| 39 | 3 | | `&none` | Disabled |
| 40 | 3 | | `&none` | Disabled |
| 41 | 3 | | `&none` | Disabled |
| 42 | 3 | Left encoder | `&none` | Disabled |
| 43 | 3 | Right encoder | `&trans` | Inherits `&tog MOUSE` from mouse layer |
| 44 | 3 | | `&none` | Disabled |
| 45 | 3 | | `&none` | Disabled |
| 46 | 3 | | `&none` | Disabled |
| 47 | 3 | | `&none` | Disabled |
| 48 | 3 | | `&none` | Disabled |
| 49 | 3 | | `&none` | Disabled |
| 50 | 4 | | `&none` | Disabled |
| 51 | 4 | | `&none` | Disabled |
| 52 | 4 | | `&none` | Disabled |
| 53 | 4 | | `&none` | Disabled |
| 54 | 4 | | `&none` | Disabled |
| 55 | 4 | | `&trans` | Inherits `&tog MOUSE` from mouse layer |
| 56 | 4 | | `&mkp LCLK` | Left Click |
| 57 | 4 | | `&mkp RCLK` | Right Click |
| 58 | 4 | | `&mkp MCLK` | Middle Click |
| 59 | 4 | | `&none` | Disabled |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

## Design Rationale

### Triple Alpha Layout Architecture

QWERTY (layer 0), Engram (layer 1), and Enthium v14 (layer 2) coexist as a unified system. The three layouts serve different use cases:

- **QWERTY** is the baseline -- universally known, required for gaming and shared-computer situations. It serves as the transparent fallback for all functional layers.
- **Engram** is optimized for English prose with its vowel-consonant hand split and custom mod-morphs that place punctuation on the base layer with logical shifted pairs (e.g., `,`/`;`, `.`/`:`, `'`/`(`, `"`/`)`). Its number row inverts the standard convention: symbols are the base output, numbers require shift.
- **Enthium v14** is an alternative optimized layout with a different finger-frequency distribution. It places `R` on a thumb key (pos 55) and uses the original v14 orientation.

Engram and Enthium are toggle overlays. When active, they replace alpha and punctuation keys but inherit the number row (for QWERTY and Enthium), thumb cluster, encoders, and modifiers from layer 0 via `&trans`. This eliminates the need to duplicate shared bindings across layouts.

The four-key combo (pos 46+47+48+49, bottom-right corner: `,`/`.`/`/`/Shift) cycles through layouts: QWERTY -> Engram -> Enthium -> QWERTY. The cycle uses `&tog` for QWERTY-to-Engram and Enthium-to-QWERTY transitions, and the `engram_to_enthium` macro (which chains `&tog ENGRAM &tog ENTHIUM` with 0ms delay) for the middle transition.

### CAGS Home Row Mods

The layout uses CAGS ordering (Ctrl-Alt-GUI-Shift from pinky to index) rather than the more common GACS or SCAG.

- **Shift on index finger:** Most frequently used modifier, placed on the fastest and strongest finger.
- **GUI (Cmd) on middle finger** with extended idle timer (`hml_g`/`hmr_g` at 350ms vs 150ms) to prevent accidental Cmd activation during fast typing.
- **Ctrl on pinky:** Used less frequently in macOS workflows, acceptable on the weaker finger.
- **All HRM behaviors** use `hold-trigger-on-release` and positional filtering (opposite hand + thumbs only trigger holds) for maximum misfire prevention.

The same CAGS order is applied consistently across all three alpha layouts (QWERTY, Engram, Enthium) with the same finger positions and the same custom hold-tap behaviors.

### Thumb Row Design per Layout

The thumb cluster is where the three layouts diverge most significantly:

**QWERTY (layer 0):**
- Left: `Ctrl/Hyper+Z` | `Alt/Hyper+B` | `GUI/Hyper+A` | `NUMBERS/Esc` | `MOUSE/Enter`
- Right: `NUMBERS/Space` | `NAV/Space` | `RGUI` | `Alt/Hyper+Y` | `FKEYS/Enter`
- Design: Two NUMBERS access points (left inner + right inner), two NAV access points (pos 24 + pos 56), MOUSE on left thumb.

**Engram (layer 1):**
- Left: `&trans` x5 (inherits QWERTY left thumbs)
- Right: `NUMBERS/Space` | `&trans` | `#/$` | `/ /\` | `&trans`
- Design: Mostly inherits from QWERTY. Positions 57 and 58 are overridden with Engram-specific mod-morphs (`#/$` and `/\`) because Engram places these symbols on the base layer.

**Enthium (layer 2):**
- Left: `&trans` x3 | `NUMBERS/Space` | `&trans`
- Right: `NUMBERS/R` | `NAV/Space` | `&trans` x3
- Design: Position 53 changes from `NUMBERS/Esc` to `NUMBERS/Space`, and position 55 changes from `NUMBERS/Space` to `NUMBERS/R`. The thumb-R is a defining feature of Enthium -- placing the high-frequency letter R on a thumb key frees a prime home row position.

### Engram Mod-Morphs

Engram's defining feature in this keymap is its extensive use of mod-morphs to create custom shifted pairs. Rather than using standard US-ANSI shift behavior (where Shift+`,` = `<`), Engram redefines shifted output for logical pairing:

- Comma/semicolon (`,`/`;`) -- both are pause punctuation
- Dot/colon (`.`/`:`) -- both are sentence/clause boundaries
- Single quote/left paren (`'`/`(`) -- opening delimiter pair
- Double quote/right paren (`"`/`)`) -- closing delimiter pair
- Question/exclamation (`?`/`!`) -- both are sentence-ending marks
- At/grave (`@`/`` ` ``) -- utility symbols
- Forward slash/backslash (`/`/`\`) -- path separator pair

The number row is also inverted: symbols (`|`, `=`, `~`, `+`, `<`, `>`, `^`, `&`, `%`, `*`) are the base output, and numbers (1-0) require holding shift. This reflects the assumption that programmers need symbols more often than raw numbers, and a dedicated NUMBERS layer handles numeric input.

### Mouse Layer

Right-hand OHAE cluster provides mouse movement at 195% of ZMK default speed (1170 units). Left-hand home row provides bare modifiers (Ctrl, Alt, Shift, GUI) for modified clicks (e.g., Ctrl+click, Shift+click). Precision mode (layer 8) reduces speed to 1/3 via pinky hold at pos 35. Three exit points (encoder presses at 42/43, thumb at 55) prevent getting stuck in mouse mode.

### Mouse Speed Constants

```
MOVE_*_FAST = 1170 units (195% of ZMK default 600)
MOVE_*_SLOW = 390 units  (1/3 of fast speed, 65% of default)
Default scroll value = 25 (ZMK_POINTING_DEFAULT_SCRL_VAL)
```

### Fat-Finger Protection

Encoder press keys (pos 42/43) sit between the innermost bottom-row alpha keys and are easy to hit accidentally along with the adjacent letter. Fat-finger combos at positions 41+42 and 44+43 output the adjacent letter instead of triggering the encoder press action, preventing accidental macro/modifier activation during fast typing. Each alpha layout has its own fat-finger combos with the correct letter for that layout's position.

### Conditional Adjust Layer

The ADJUST layer (5) is only accessible by holding both NAV and NUMBERS simultaneously. This two-layer activation requirement prevents accidental access to dangerous actions (BT profile changes, power toggle, layout toggles). Since NAV is on the right thumb and NUMBERS is on the left thumb (or either inner thumb), both hands must be engaged to reach ADJUST.

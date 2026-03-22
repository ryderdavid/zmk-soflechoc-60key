## Context

The keymap grew to 18 layers with conditional layers for every combination of layout × mode (caps, windows). This change strips it back to essentials: three alpha layouts (QWERTY, Engram, Enthium) plus functional layers (numbers, nav, numpad, adjust, fkeys, mouse, prec).

## New Layer Architecture

| Index | Define | Display Name | Purpose |
|-------|--------|-------------|---------|
| 0 | QWERTY | qwerty | Base QWERTY with CAGS HRM |
| 1 | ENGRAM | bvhzql | Engram BVh ZQl toggle overlay |
| 2 | ENTHIUM | enthium | Enthium v14 toggle overlay (original orientation) |
| 3 | NUMBERS | numbers | Number grid + numpad (merged) |
| 4 | NAV | nav | Navigation, screenshots, arrows |
| 5 | ADJUST | adjust | BT, power, layout toggles |
| 6 | FKEYS | fkeys | F1-F12 + media |
| 7 | MOUSE | mouse | Mouse movement |
| 8 | PREC | prec | Precision mouse |

9 layers total. No conditional layers needed (no caps/windows mode combos). NUMPAD removed — its functionality is merged into NUMBERS.

## Alpha Layout Mappings

### Engram BVh ZQl (from image)

```
LEFT:                    RIGHT:
  _  Y  O  U  (          )  L  D  W  _
  B  C  I  E  A          H  T  S  N  V
  Z  G  X  J  K          R  M  F  P  Q
```

Outer columns have punctuation: ` ' @ on far left, ; : _ on inner left, etc. For the Sofle mapping, the alpha keys go to rows 1-3 (positions 13-17, 18-22 / 25-28, 31-34 / 37-41, 44-48), with outer positions (12, 23, 24, 35, 36, 49) inheriting from base via `&trans` or getting layer-taps.

**Engram home row with CAGS HRM:**
- 24: `&lts NAV B` (hold=Nav, tap=B)
- 25: `&hml LCTRL C` (pinky)
- 26: `&hml LALT I` (ring)
- 27: `&hml_g LGUI E` (middle, gui variant)
- 28: `&hml LSHFT A` (index)
- 29: `&lts NUMBERS SEMI` (hold=Numbers, tap=;)
- 30: `&lts NUMBERS COLON` (hold=Numbers, tap=:) — wait, Engram doesn't have : there. Let me re-read the image.

Actually from the image:
- Left inner column (pos 29): `;` with `_` below → `&lts NUMBERS SEMI`
- Right inner column (pos 30): `:` with `.` below → actually the image shows `: .` stacked. The top is `:` and bottom is `.`. But wait, this is the inner column which maps to position 30.

Let me re-map more carefully from the image:

**Row 0 (number row):** `{ |  =  ~  +  <` | `>  ^  &  %  *  }` — these are the Engram number row. On Sofle, Row 0 stays `&trans` (inherits QWERTY 1-9-0).

**Row 1 (positions 13-17, 18-22):**
- Left: `_ Y O U (` — but `_` and `(` are punctuation. Actually the image shows:
  - Far left (pos 12): `` ` `` / `@` — keep `&trans` (inherit Tab/Nav)
  - 13: (blank/gray in image) → Y? No, the image shows the second column from left on row 1 is blank/gray, then Y, O, U, then `(` / `'`.

Let me read the image more carefully. The Engram BVh ZQl layout from the image:

```
Row 1 (upper):
  Left:  `/@    [gray]   Y    O    U    (/
  Right: )/"     L       D    W   [gray] [gray]

Row 2 (home):
  Left:  B       C       I    E    A    ;/_
  Right: :/.     H       T    S    N    V

Row 3 (lower):
  Left:  Z       G       X    J    K    -/-
  Right: !/      R       M    F    P    Q
```

Hmm, the gray keys in the image are blank (no letter). The Engram layout has 5 alpha keys per hand per row on the inner columns, with punctuation on the outer columns.

For the Sofle mapping (5 alpha columns + 1 outer per hand per row):

**Row 1 (positions 12-23):**
- 12: `&trans` (Tab/Nav from base)
- 13: blank in Engram → `&trans`? Or this IS the first alpha column...

Actually, looking at the image again more carefully:
- The left hand has 6 columns total on each row
- Row 1 left: `` ` @ `` | (gray) | Y | O | U | `( '`
- The gray key might just be an unused position

For Sofle positions 13-17 (5 keys): the alpha keys are Y, O, U, and the gray positions are non-alpha. Since Engram only has 3 alphas on the upper left, positions 13-14 could be `&trans`.

Wait, I think I'm overcomplicating this. Let me map it the same way Enthium does — 5 columns per hand for Row 1:

**Row 1 left (13-17):** `&trans` `Y` `O` `U` `&trans`  (only 3 alphas; outer positions transparent)

No, that leaves too many gaps. Let me look at standard Engram 2.0 positioning for a 5-column split:

Standard Engram 2.0 (5 columns per hand):
```
Left:  b y o u '    Right: " l d w v
       c i e a ,           . h t s n
       g x j k -           - r m f p
```

But BVh ZQl swaps B/V to home row and Z/Q to bottom:
```
Left:    y o u        Right:   l d w
       b c i e a           h t s n v
       z g x j k           r m f p q
```

Yes — the image confirms this. Row 1 has only 3 alphas per hand (Y O U / L D W). So:

**Row 1 (positions 13-17, 18-22):**
- 13: `&trans` (no alpha, inherit Q from base)
- 14: `&kp Y`
- 15: `&kp O`
- 16: `&kp U`
- 17: `&trans` (no alpha, inherit T from base) → OR put punctuation `(` here

Actually for a toggle overlay, blanks should be `&trans` to inherit the base layer key. This means on the Engram layer, position 13 would show Q (from QWERTY base) which is wrong. We need to put SOMETHING there or `&none`.

For Engram, the outer positions on Row 1 aren't alpha keys — they're punctuation in the full Engram layout. The image shows `` ` @ `` on far left and `( '` on inner left. For simplicity: put those punctuation keys there.

- 13: `&kp GRAVE` (`` ` ``)
- 14: `&kp Y`
- 15: `&kp O`
- 16: `&kp U`
- 17: `&kp LPAR` (`(`)
- 18: `&kp RPAR` (`)`)
- 19: `&kp L`
- 20: `&kp D`
- 21: `&kp W`
- 22: `&trans` (inherit P from base → wrong. Need `&none` or something)

Hmm, this is getting messy. Let me take the simpler approach: put ALL the Engram letters in the right positions and use `&none` for positions that Engram doesn't define:

**Row 1 left (13-17):** `&none` `&kp Y` `&kp O` `&kp U` `&none`
**Row 1 right (18-22):** `&none` `&kp L` `&kp D` `&kp W` `&none`

**Row 2 home (24-35):** Full 5+5 alphas + layer-taps on edges:
- 24: `&lts NAV B`
- 25: `&hml LCTRL C`
- 26: `&hml LALT I`
- 27: `&hml_g LGUI E`
- 28: `&hml LSHFT A`
- 29: `&lts NUMBERS SEMI`
- 30: `&lts NUMBERS COLON`... wait, COLON isn't a base keycode, it's LS(SEMI). Use something else. Actually, looking at the image, the right inner column shows `: .` stacked, meaning the key produces `:` (which is Shift+;). For a layer-tap: `&lts NUMBERS LS(SEMI)` — but ZMK might not allow shifted keys as lts params. Alternative: just use `&trans` to inherit from base.

Let me use `&trans` for the inner positions (29, 30) to inherit the Numbers layer-tap from base, since those positions already have `&lts NUMBERS G` and `&lts NUMBERS H` in QWERTY.

- 29: `&trans` (inherit &lts NUMBERS G from base)
- 30: `&trans` (inherit &lts NUMBERS H from base)
- 31: `&hmr RSHFT H`
- 32: `&hmr_g RGUI T`
- 33: `&hmr RALT S`
- 34: `&hmr RCTRL N`
- 35: `&lts NAV V`

**Row 3 (37-41, 44-48):**
- 37: `&kp Z`
- 38: `&kp G`
- 39: `&kp X`
- 40: `&kp J`
- 41: `&lts MOUSE K` (hold=Mouse)
- 44: `&kp R`
- 45: `&kp M`
- 46: `&kp F`
- 47: `&kp P`
- 48: `&kp Q`

**Thumb:** All `&trans` (inherit from base).

### Enthium v14 (original, NOT mirrored)

```
LEFT:                RIGHT:
q y o u =            x l d p z
b c i a e            k h t n s
' , . ; /            j m g f v
                     r (right thumb)
```

This is the opposite of what's currently on the board (which is mirrored). The mapping:

**Row 1 (13-17, 18-22):**
- 13: `&kp Q`, 14: `&kp Y`, 15: `&kp O`, 16: `&kp U`, 17: `&kp EQUAL`
- 18: `&kp X`, 19: `&kp L`, 20: `&kp D`, 21: `&kp P`, 22: `&kp Z`

**Row 2 home (24-35) with CAGS HRM:**
- 24: `&lts NAV B`
- 25: `&hml LCTRL C`
- 26: `&hml LALT I`
- 27: `&hml_g LGUI A`
- 28: `&hml LSHFT E`
- 29: `&trans` (inherit Numbers)
- 30: `&trans` (inherit Numbers)
- 31: `&hmr RSHFT H`
- 32: `&hmr_g RGUI T`
- 33: `&hmr RALT N`
- 34: `&hmr RCTRL S`
- 35: `&lts NAV W` — wait, Enthium has `s` and `w` on the right home, but those are 6th column. The 5-column core is `k h t n s`. Position 35 (far right home) needs `W`? No — Enthium's right home is `k h t n s` (5 keys) plus `w` on the 6th column. But `w` isn't in the core 5-column Enthium.

Actually, Enthium's home row is `b c i a e - k h t n s w` (12 keys for 6-column boards). For the Sofle:
- 30: `&lts NUMBERS K`
- 31: `&hmr RSHFT H`
- 32: `&hmr_g RGUI T`
- 33: `&hmr RALT N`
- 34: `&hmr RCTRL S`
- 35: `&lts NAV W`

And the `-` at position 29 for Enthium: `&lts NUMBERS MINUS`

**Row 3 (37-41, 44-48):**
- 37: `&kp SQT`, 38: `&kp COMMA`, 39: `&kp DOT`, 40: `&kp SEMI`, 41: `&lts MOUSE FSLH`
- 44: `&kp J`, 45: `&kp M`, 46: `&kp G`, 47: `&kp F`, 48: `&kp V`

**Thumb:** R on the far inner right thumb key. User wants Space on far inner right too. Position 55 (innermost right thumb) gets `&lts NUMBERS R`? No — user said "space on the far inner righthand thumbkey." So position 55 should be Space, and R goes on position 56 or another thumb.

Actually wait: "make it have space on the far inner righthand thumbkey." The far inner right thumb is position 55. Currently base has `&lts SYMBOLS ENTER` there (but SYMBOLS is being removed). So position 55 could become `&kp SPACE` or `&lts NUMBERS SPACE`.

And R needs a thumb position. If Space is at 55, R could go at 56: `&lts NAV R`.

For the Enthium thumb row:
- 53: `&trans` (inherit base)
- 54: `&trans` (inherit Mouse/Enter)
- 55: `&kp SPACE` (far inner right = Space)
- 56: `&lts NAV R` (hold=Nav, tap=R)
- 57-59: `&trans`

### Removed Layers

Layers being removed and their current indices:
- GALLIUM (1)
- SYMBOLS (5) — removed
- WINMODE (11), WINMODE_GALLIUM (12), WINMODE_MOUSE (13)
- CAPS_DISPLAY (14), GALLIUM_CAPS (15)
- ENTHIUM_CAPS (16), ENTHIUM_WIN (17)

### Removed Combos
- All Gallium combos (mouse_toggle_g, fatfinger_del_g, fatfinger_bksp_g)
- layout_to_gallium, layout_to_enthium (replaced with new cycle)
- winmode_toggle
- shift_caps
- numbers_toggle (optional — could keep)

### Removed Behaviors
- `td_caps` (no caps toggle)
- `td_shift` (no caps toggle — use plain `&kp LSHFT` at pos 36)
- `caps` behavior (caps-word — could keep as a combo if desired)
- `gallium_to_enthium` macro (replaced)

### Removed Includes
- `#include "corne-canon-chords.dtsi"` (word chords removed)

### Cycle Toggle

Three combos at positions 46+47+48+49:
- `layout_to_engram`: layers=<QWERTY>, action=`&tog ENGRAM`
- `layout_to_enthium`: layers=<ENGRAM>, action: macro `&engram_to_enthium` (tog ENGRAM, tog ENTHIUM)
- `layout_to_qwerty`: layers=<ENTHIUM>, action=`&tog ENTHIUM`

### Base Layer Thumb Row (kept from previous changes)
- 50: `&htk LCTRL LS(LC(LA(LG(Z))))` (Ctrl/Hyper)
- 51: `&htk LALT LS(LC(LA(LG(B))))` (Alt/Hyper)
- 52: `&htk LGUI LS(LC(LA(LG(A))))` (GUI/Hyper)
- 53: `&lts NAV ENTER` (hold=Nav, was Sym/Enter but Symbols removed — change to Nav?)
- 54: `&lts MOUSE ENTER` (hold=Mouse)
- 55: `&lts NAV SPACE` (hold=Nav, tap=Space) — with SYMBOLS removed, this changes
- 56: `&lts NAV SPACE` (same as before)
- 57: `&kp RGUI` (Cmd only)
- 58: `&htk RALT LS(LC(LA(LG(Y))))` (Alt/Hyper)
- 59: `&lts FKEYS ENTER` (Fkeys)

Wait — with SYMBOLS layer removed, the `&lts SYMBOLS ...` bindings at positions 53 and 55 need to change. Options:
- 53: `&lts NAV ENTER` or `&lts NUMPAD ENTER`
- 55: `&lts NUMPAD SPACE` or just `&kp SPACE`

For Enthium specifically: position 55 = Space (user request), position 56 = R/Nav.

Let me define the base thumb row with SYMBOLS removed:
- 53: `&lts NUMPAD ENTER` (hold=Numpad, tap=Enter)
- 55: `&kp SPACE` (just Space, no layer hold)
- 56: `&lts NAV SPACE` (hold=Nav, tap=Space)

Then Enthium overrides:
- 55: `&kp SPACE` (same as base, could be &trans)
- 56: `&lts NAV R` (hold=Nav, tap=R)

And Engram: all `&trans` on thumbs.

## Conditional Layers

Only one conditional remains:
- NAV + NUMPAD → ADJUST (or we could just make Adjust accessible differently)

Actually, the current conditional is NAV + SYMBOLS → ADJUST. With SYMBOLS removed, we need a new trigger. Options:
- NAV + NUMPAD → ADJUST
- Keep ADJUST as a standalone momentary layer via a combo or thumb key

Use NAV + NUMPAD → ADJUST since both are commonly held.

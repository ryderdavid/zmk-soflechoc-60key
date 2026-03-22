# Profile: Enthium

**Description:** Original Enthium v14 layout adapted to Sofle (60-key). Vowels (Y O U, I A E) on the LEFT hand, consonants (L D P, H T N S) on the RIGHT. Single toggle overlay layer (layer 2) with CAGS home row mods on both hands.

**Based on:** Enthium v14 (original orientation)

**HRM Order:** CAGS (Ctrl-Alt-GUI-Shift, pinky to index)

**Source file:** `config/sofle.keymap`

---

## Layer Architecture

| Index | Define | Display Name | Purpose | Activation |
|-------|--------|-------------|---------|------------|
| 2 | `ENTHIUM` | enthium | Original Enthium v14 alpha overlay | Toggle (combo: pos 46+47+48+49 from Engram) |

The Enthium overlay sits at layer index 2, between Engram (1) and Numbers (3). All non-alpha keys on rows 0 and the thumb cluster are `&trans` to inherit from the QWERTY base (layer 0). The layout cycle combo at positions 46+47+48+49 rotates: QWERTY -> Engram -> Enthium -> QWERTY.

No caps-conditional or Windows-mode layers exist for Enthium in the current keymap. Only the single alpha overlay at index 2.

---

## Layout Cycle Combo

The bottom-right corner combo (positions 46+47+48+49) cycles through all three alpha layouts:

| Source Layer | Binding | Effect |
|--------------|---------|--------|
| QWERTY (0) | `&tog ENGRAM` | Activates Engram |
| ENGRAM (1) | `&engram_to_enthium` | Macro: `&tog ENGRAM &tog ENTHIUM` (deactivates Engram, activates Enthium) |
| ENTHIUM (2) | `&tog ENTHIUM` | Deactivates Enthium, returns to QWERTY |

The `engram_to_enthium` macro fires `&tog ENGRAM &tog ENTHIUM` with zero delay, atomically switching between the two toggle overlays.

---

## Enthium-Specific Combos

| Name | Positions | Layers | Binding | Notes |
|------|-----------|--------|---------|-------|
| fatfinger_del_e | 41+42 | ENTHIUM (2) | `&kp FSLH` | `/` -- the key at pos 41 on Enthium is Mouse/`/` |
| fatfinger_bksp_e | 44+43 | ENTHIUM (2) | `&kp J` | J -- the key at pos 44 on Enthium is J |
| layout_to_qwerty | 46+47+48+49 | ENTHIUM (2) | `&tog ENTHIUM` | Bottom-right corner exits Enthium |

---

## Enthium v14 Original Orientation

Standard Enthium v14 places vowels on the left hand and consonants on the right. This profile preserves that original orientation directly, unlike the previous mirrored version. The key advantage is that the vowel cluster (I, A, E on the left home row) naturally pairs with the CAGS modifier order: the most common vowels sit under the strongest fingers (index and middle), while modifiers progress outward (Shift on index, GUI on middle, Alt on ring, Ctrl on pinky).

### Alpha Grid (Rows 1-3)

```
LEFT HAND                          RIGHT HAND
  Q   Y   O   U   =                 X   L   D   P   Z
  B   C   I   A   E   -         K   H   T   N   S   W
  !   '   ,   .   ;  Mouse//        J   M   G   F   V   !
```

---

## Full Binding Table

### Layer 2: enthium (Original Enthium v14 alpha overlay)

Toggle overlay that replaces alpha and punctuation keys with Enthium v14 positions in the original orientation. Vowels (Y O U / I A E) are on the left hand, consonants (L D P / H T N S) are on the right. The top row (row 0), encoder keys, and most thumb keys are `&trans` to inherit from the QWERTY base (layer 0).

#### Row 0 -- Number Row (Positions 0-11)

| Pos | Binding | Hold | Tap | Notes |
|-----|---------|------|-----|-------|
| 0 | `&trans` | -- | -- | Inherits `Numbers/`` ` `` from QWERTY (`&lts NUMBERS GRAVE`) |
| 1 | `&trans` | -- | -- | Inherits `1` |
| 2 | `&trans` | -- | -- | Inherits `2` |
| 3 | `&trans` | -- | -- | Inherits `3` |
| 4 | `&trans` | -- | -- | Inherits `4` |
| 5 | `&trans` | -- | -- | Inherits `5` |
| 6 | `&trans` | -- | -- | Inherits `6` |
| 7 | `&trans` | -- | -- | Inherits `7` |
| 8 | `&trans` | -- | -- | Inherits `8` |
| 9 | `&trans` | -- | -- | Inherits `9` |
| 10 | `&trans` | -- | -- | Inherits `0` |
| 11 | `&trans` | -- | -- | Inherits Backspace |

#### Row 1 -- Upper Alpha Row (Positions 12-23)

| Pos | Binding | Hold | Tap | Notes |
|-----|---------|------|-----|-------|
| 12 | `&trans` | -- | -- | Inherits Tab from QWERTY |
| 13 | `&kp Q` | -- | Q | Left pinky |
| 14 | `&kp Y` | -- | Y | Left ring |
| 15 | `&kp O` | -- | O | Left middle |
| 16 | `&kp U` | -- | U | Left index |
| 17 | `&kp EQUAL` | -- | `=` | Left inner index -- punctuation on alpha grid |
| 18 | `&kp X` | -- | X | Right inner index |
| 19 | `&kp L` | -- | L | Right index |
| 20 | `&kp D` | -- | D | Right middle |
| 21 | `&kp P` | -- | P | Right ring |
| 22 | `&kp Z` | -- | Z | Right pinky |
| 23 | `&trans` | -- | -- | Inherits `-` from QWERTY (right outer) |

#### Row 2 -- Home Row (Positions 24-35)

This is the core of Enthium: vowels I A E under left CAGS mods, consonants H T N S under right CAGS mods.

| Pos | Binding | Hold | Tap | Notes |
|-----|---------|------|-----|-------|
| 24 | `&lts NAV B` | NAV layer | B | Left outer pinky -- layer-tap for navigation |
| 25 | `&hml LCTRL C` | Left Ctrl | C | CAGS pinky (Ctrl) |
| 26 | `&hml LALT I` | Left Alt | I | CAGS ring (Alt) -- vowel |
| 27 | `&hml_g LGUI A` | Left GUI | A | CAGS middle (GUI, 350ms idle) -- vowel |
| 28 | `&hml LSHFT E` | Left Shift | E | CAGS index (Shift) -- vowel |
| 29 | `&kp MINUS` | -- | `-` | Left inner -- plain minus, no layer-tap |
| 30 | `&kp K` | -- | K | Right inner -- plain K, no layer-tap |
| 31 | `&hmr RSHFT H` | Right Shift | H | CAGS index (Shift) -- consonant |
| 32 | `&hmr_g RGUI T` | Right GUI | T | CAGS middle (GUI, 350ms idle) -- consonant |
| 33 | `&hmr RALT N` | Right Alt | N | CAGS ring (Alt) -- consonant |
| 34 | `&hmr RCTRL S` | Right Ctrl | S | CAGS pinky (Ctrl) -- consonant |
| 35 | `&lts NAV W` | NAV layer | W | Right outer pinky -- layer-tap for navigation |

#### Row 3 -- Bottom Row (Positions 36-49)

| Pos | Binding | Hold | Tap | Notes |
|-----|---------|------|-----|-------|
| 36 | `&mt LSHFT EXCL` | Left Shift | `!` | Mod-tap: hold=Shift, tap=`!` |
| 37 | `&kp SQT` | -- | `'` | Apostrophe |
| 38 | `&kp COMMA` | -- | `,` | Comma |
| 39 | `&kp DOT` | -- | `.` | Period |
| 40 | `&kp SEMI` | -- | `;` | Semicolon |
| 41 | `&lts MOUSE FSLH` | MOUSE layer | `/` | Layer-tap: hold=Mouse, tap=`/` |
| 42 | `&trans` | -- | -- | Left encoder press -- inherits Hyper from QWERTY |
| 43 | `&trans` | -- | -- | Right encoder press -- inherits Meh from QWERTY |
| 44 | `&kp J` | -- | J | Right inner index |
| 45 | `&kp M` | -- | M | |
| 46 | `&kp G` | -- | G | |
| 47 | `&kp F` | -- | F | |
| 48 | `&kp V` | -- | V | |
| 49 | `&mt RSHFT EXCL` | Right Shift | `!` | Mod-tap: hold=Shift, tap=`!` -- mirrors pos 36 |

#### Row 4 -- Thumb Cluster (Positions 50-59)

| Pos | Binding | Hold | Tap | Notes |
|-----|---------|------|-----|-------|
| 50 | `&trans` | -- | -- | Inherits `Ctrl/Hyper+Z` from QWERTY (`&htk LCTRL LS(LC(LA(LG(Z))))`) |
| 51 | `&trans` | -- | -- | Inherits `Alt/Hyper+B` from QWERTY (`&htk LALT LS(LC(LA(LG(B))))`) |
| 52 | `&trans` | -- | -- | Inherits `GUI/Hyper+A` from QWERTY (`&htk LGUI LS(LC(LA(LG(A))))`) |
| 53 | `&lts NUMBERS SPACE` | NUMBERS layer | Space | **Left primary thumb** -- hold=Numbers, tap=Space |
| 54 | `&trans` | -- | -- | Inherits `Mouse/Enter` from QWERTY (`&lts MOUSE ENTER`) |
| 55 | `&lts NUMBERS R` | NUMBERS layer | R | **Right primary thumb** -- hold=Numbers, tap=R |
| 56 | `&lts NAV SPACE` | NAV layer | Space | **Right secondary thumb** -- hold=Nav, tap=Space |
| 57 | `&trans` | -- | -- | Inherits `RGUI` from QWERTY (`&kp RGUI`) |
| 58 | `&trans` | -- | -- | Inherits `Alt/Hyper+Y` from QWERTY (`&htk RALT LS(LC(LA(LG(Y))))`) |
| 59 | `&trans` | -- | -- | Inherits `Fkeys/Enter` from QWERTY (`&lts FKEYS ENTER`) |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

## Design Rationale

### Original (Non-Mirrored) Orientation

This layout preserves Enthium v14's original hand assignment: vowels on the left, consonants on the right. The previous mirrored version swapped hands to free a thumb position for R, but the original orientation was restored for several reasons:

1. **Familiarity with Enthium reference material.** The original orientation matches all published Enthium documentation and frequency analyses, making it easier to compare and verify.

2. **Natural vowel-modifier pairing.** With CAGS HRM (Ctrl-Alt-GUI-Shift from pinky to index), the left hand's vowel cluster (C/Ctrl, I/Alt, A/GUI, E/Shift) places the highest-frequency vowels (E, A) under the strongest modifiers (Shift, GUI). This is ergonomically sound because vowels are typed frequently during prose, and the balanced flavor hold-tap with `require-prior-idle-ms` prevents misfires during fast vowel sequences.

3. **Consonant cluster on the right.** The right home row (H/Shift, T/GUI, N/Alt, S/Ctrl) groups the four most common consonants in English together. T and N under GUI and Alt respectively means the most-used consonants get the least-fatiguing finger positions.

### Thumb Layout

The thumb cluster is the most significant departure from both standard Enthium and the previous mirrored version:

- **Position 53 (`Numbers/Space`):** The left primary thumb produces Space on tap and activates the Numbers layer on hold. Space is the most-pressed key; placing it under the left thumb balances the workload since the right hand handles more consonant keys.

- **Position 55 (`Numbers/R`):** R moves to the right primary thumb as a layer-tap with Numbers. R is the 5th most common English letter. Placing it on the thumb frees a home row position and reduces finger travel. The Numbers layer on hold provides a second entry point to the number grid (matching pos 53), so either thumb can activate it.

- **Position 56 (`Nav/Space`):** A second Space on the right secondary thumb, with Nav layer on hold. Having Space on both thumbs means the non-dominant hand can always produce Space regardless of which hand just typed an alpha key, reducing alternation delays.

- **Positions 50-52 and 57-59 are `&trans`**, inheriting the QWERTY base layer's modifier and utility bindings (Ctrl/Hyper+Z, Alt/Hyper+B, GUI/Hyper+A on the left; RGUI, Alt/Hyper+Y, Fkeys/Enter on the right). This keeps system shortcuts consistent across all three alpha layouts.

### Positions 29 and 30: Plain Keys (No Layer-Tap)

Unlike the Engram profile (which uses `&mm_comma_semi` and `&mm_dot_colon` at the inner home positions) and unlike the previous mirrored Enthium (which used `&lts NUMBERS K` and `&lts NUMBERS MINUS`), the current Enthium uses plain `&kp MINUS` at position 29 and plain `&kp K` at position 30. Numbers layer access is handled entirely through the thumb keys (positions 53 and 55), keeping the home row free of layer-tap complexity and reducing the risk of misfires on these high-frequency inner index positions.

### Positions 24 and 35: Nav Layer-Taps

The outer home row pinkies use `&lts NAV B` (left, pos 24) and `&lts NAV W` (right, pos 35), providing NAV layer access on hold with low-frequency alpha keys (B and W) on tap. This is the primary Nav entry point, consistent with the QWERTY base layer's `&mo NAV` at position 24 and `&lts NAV SQT` at position 35.

### Position 41: Mouse Layer Access

Position 41 uses `&lts MOUSE FSLH` -- hold activates the Mouse layer, tap produces `/`. This places mouse control access on the left inner bottom row, easily reachable by the left index finger. The `/` character on tap integrates a common punctuation mark into the alpha grid.

### Positions 36 and 49: Shift/Exclamation

Both outer bottom-row positions use `&mt (L/R)SHFT EXCL` -- hold for Shift, tap for `!`. This symmetric placement gives both hands access to Shift (useful when the opposite hand needs to produce a shifted character) and puts `!` on a single tap without requiring the number row. This matches Enthium's punctuation philosophy of integrating common symbols directly into the base layer.

### Bottom-Row Punctuation (Positions 37-40)

The left bottom row places apostrophe, comma, period, and semicolon in sequence (`' , . ;`). These are the most common English punctuation marks and having them in a natural left-to-right reading order on the bottom row provides quick access without leaving the alpha layer.

### Fat-Finger Combos

The Enthium fat-finger combos protect against accidental encoder presses:
- Positions 41+42 (left encoder area) produce `/` -- the key already at position 41
- Positions 44+43 (right encoder area) produce `J` -- the key already at position 44

This means accidentally hitting the encoder key alongside its neighbor produces the intended alpha/punctuation character rather than a stray encoder press.

# Profile: Engram BVh ZQl

**Description:** Engram BVh ZQl layout adapted to Sofle (60-key). A variant of Arno's Engram 2.0 with B and V on the home row outer positions and Z and Q on the lower row outer positions. Features 18 mod-morph behaviors for Engram's custom shifted pairs: symbol-first number row (symbols on base, digits on shift) and remapped punctuation pairs.

**Based on:** Engram 2.0 (BVh ZQl variant)

**HRM Order:** CAGS (Ctrl-Alt-GUI-Shift, pinky to index)

**Source file:** `config/sofle.keymap`

---

## Layer Architecture (Engram-specific)

| Index | Define | Display Name | Purpose | Activation |
|-------|--------|-------------|---------|------------|
| 1 | `ENGRAM` | bvhzql | Engram BVh ZQl alpha overlay | Toggle (combo: pos 46+47+48+49 from QWERTY) |

The Engram overlay sits at layer index 1, between QWERTY (0) and Enthium (2). Non-alpha/non-Engram keys use `&trans` to inherit from the QWERTY base (layer 0). The layout cycle combo at positions 46+47+48+49 rotates: QWERTY -> Engram -> Enthium -> QWERTY.

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

## Engram-Specific Combos

| Name | Positions | Layers | Binding | Notes |
|------|-----------|--------|---------|-------|
| fatfinger_del_eng | 41+42 | ENGRAM (1) | `&kp K` | K is adjacent to encoder at pos 41 |
| fatfinger_bksp_eng | 44+43 | ENGRAM (1) | `&kp R` | R is adjacent to encoder at pos 44 |
| layout_to_enthium | 46+47+48+49 | ENGRAM (1) | `&engram_to_enthium` | Bottom-right corner advances to Enthium |

---

## Mod-Morph Behaviors (18 total)

Engram uses mod-morph behaviors to implement custom shifted pairs that differ from standard US keyboard layout. The base character is produced on tap; holding Shift produces the morph character instead of the standard shifted symbol.

### Punctuation Mod-Morphs

| Behavior | Base (tap) | Shifted | Notes |
|----------|-----------|---------|-------|
| `&mm_comma_semi` | `,` | `;` | Home row left inner |
| `&mm_dot_colon` | `.` | `:` | Home row right inner |
| `&mm_sqt_lpar` | `'` | `(` | Upper row left |
| `&mm_dqt_rpar` | `"` | `)` | Upper row right |
| `&mm_qmark_excl` | `?` | `!` | Lower row right |
| `&mm_at_grave` | `@` | `` ` `` | Row 0 leftmost |
| `&mm_hash_dllr` | `#` | `$` | Thumb cluster |
| `&mm_fslh_bslh` | `/` | `\` | Thumb cluster |

### Number Row Mod-Morphs (symbol-first)

| Behavior | Base (tap) | Shifted | Position |
|----------|-----------|---------|----------|
| `&mm_pipe_n1` | `\|` | `1` | Pos 1 |
| `&mm_equal_n2` | `=` | `2` | Pos 2 |
| `&mm_tilde_n3` | `~` | `3` | Pos 3 |
| `&mm_plus_n4` | `+` | `4` | Pos 4 |
| `&mm_lt_n5` | `<` | `5` | Pos 5 |
| `&mm_gt_n6` | `>` | `6` | Pos 6 |
| `&mm_caret_n7` | `^` | `7` | Pos 7 |
| `&mm_amps_n8` | `&` | `8` | Pos 8 |
| `&mm_prcnt_n9` | `%` | `9` | Pos 9 |
| `&mm_astrk_n0` | `*` | `0` | Pos 10 |

---

## Full Binding Table

### Layer 1: bvhzql (Engram BVh ZQl alpha overlay)

Toggle overlay that replaces alpha keys and punctuation with Engram positions. The number row uses symbol-first mod-morphs (symbols on base tap, digits when shifted). Home row features CAGS HRM with Engram letters. Outer home row positions use layer-taps: B/Nav (pos 24) and V/Nav (pos 35). Lower row outer positions use mod-taps: Z/Shift (pos 36) and Q/Shift (pos 49). Thumb cluster is mostly `&trans` except for Numbers/Space (pos 55) and two mod-morphs (#/$ at pos 58, / /\ at pos 59... wait -- let me re-check).

| Pos | Row | Physical Key | Binding | Hold | Tap | Shifted | Notes |
|-----|-----|-------------|---------|------|-----|---------|-------|
| 0 | 0 | Top-left | `&mm_at_grave` | -- | `@` | `` ` `` | Mod-morph: tap=@, shift=` |
| 1 | 0 | | `&mm_pipe_n1` | -- | `\|` | `1` | Mod-morph: tap=\|, shift=1 |
| 2 | 0 | | `&mm_equal_n2` | -- | `=` | `2` | Mod-morph: tap==, shift=2 |
| 3 | 0 | | `&mm_tilde_n3` | -- | `~` | `3` | Mod-morph: tap=~, shift=3 |
| 4 | 0 | | `&mm_plus_n4` | -- | `+` | `4` | Mod-morph: tap=+, shift=4 |
| 5 | 0 | | `&mm_lt_n5` | -- | `<` | `5` | Mod-morph: tap=<, shift=5 |
| 6 | 0 | | `&mm_gt_n6` | -- | `>` | `6` | Mod-morph: tap=>, shift=6 |
| 7 | 0 | | `&mm_caret_n7` | -- | `^` | `7` | Mod-morph: tap=^, shift=7 |
| 8 | 0 | | `&mm_amps_n8` | -- | `&` | `8` | Mod-morph: tap=&, shift=8 |
| 9 | 0 | | `&mm_prcnt_n9` | -- | `%` | `9` | Mod-morph: tap=%, shift=9 |
| 10 | 0 | | `&mm_astrk_n0` | -- | `*` | `0` | Mod-morph: tap=*, shift=0 |
| 11 | 0 | Top-right | `&kp BSPC` | -- | Backspace | -- | |
| 12 | 1 | | `&kp TAB` | -- | Tab | -- | |
| 13 | 1 | | `&none` | -- | -- | -- | Unused position |
| 14 | 1 | Y | `&kp Y` | -- | Y | -- | |
| 15 | 1 | O | `&kp O` | -- | O | -- | |
| 16 | 1 | U | `&kp U` | -- | U | -- | |
| 17 | 1 | | `&mm_sqt_lpar` | -- | `'` | `(` | Mod-morph: tap=', shift=( |
| 18 | 1 | | `&mm_dqt_rpar` | -- | `"` | `)` | Mod-morph: tap=", shift=) |
| 19 | 1 | L | `&kp L` | -- | L | -- | |
| 20 | 1 | D | `&kp D` | -- | D | -- | |
| 21 | 1 | W | `&kp W` | -- | W | -- | |
| 22 | 1 | | `&kp LBKT` | -- | `[` | -- | |
| 23 | 1 | | `&kp RBKT` | -- | `]` | -- | |
| 24 | 2 | Home-left outer | `&lts NAV B` | NAV layer | B | -- | Layer-tap: hold=Nav, tap=B |
| 25 | 2 | C | `&hml LCTRL C` | Left Ctrl | C | -- | CAGS pinky |
| 26 | 2 | I | `&hml LALT I` | Left Alt | I | -- | CAGS ring |
| 27 | 2 | E | `&hml_g LGUI E` | Left GUI | E | -- | CAGS middle (350ms idle) |
| 28 | 2 | A | `&hml LSHFT A` | Left Shift | A | -- | CAGS index |
| 29 | 2 | | `&mm_comma_semi` | -- | `,` | `;` | Mod-morph: tap=comma, shift=semi |
| 30 | 2 | | `&mm_dot_colon` | -- | `.` | `:` | Mod-morph: tap=dot, shift=colon |
| 31 | 2 | H | `&hmr RSHFT H` | Right Shift | H | -- | CAGS index |
| 32 | 2 | T | `&hmr_g RGUI T` | Right GUI | T | -- | CAGS middle (350ms idle) |
| 33 | 2 | S | `&hmr RALT S` | Right Alt | S | -- | CAGS ring |
| 34 | 2 | N | `&hmr RCTRL N` | Right Ctrl | N | -- | CAGS pinky |
| 35 | 2 | Home-right outer | `&lts NAV V` | NAV layer | V | -- | Layer-tap: hold=Nav, tap=V |
| 36 | 3 | Left shift | `&mt LSHFT Z` | Left Shift | Z | -- | Mod-tap: hold=Shift, tap=Z |
| 37 | 3 | G | `&kp G` | -- | G | -- | |
| 38 | 3 | X | `&kp X` | -- | X | -- | |
| 39 | 3 | J | `&kp J` | -- | J | -- | |
| 40 | 3 | K | `&kp K` | -- | K | -- | |
| 41 | 3 | | `&kp MINUS` | -- | `-` | -- | |
| 42 | 3 | Left encoder | `&trans` | -- | -- | -- | Inherits Hyper macro from QWERTY |
| 43 | 3 | Right encoder | `&trans` | -- | -- | -- | Inherits Meh macro from QWERTY |
| 44 | 3 | | `&mm_qmark_excl` | -- | `?` | `!` | Mod-morph: tap=?, shift=! |
| 45 | 3 | R | `&kp R` | -- | R | -- | |
| 46 | 3 | M | `&kp M` | -- | M | -- | |
| 47 | 3 | F | `&kp F` | -- | F | -- | |
| 48 | 3 | P | `&kp P` | -- | P | -- | |
| 49 | 3 | Right shift | `&mt RSHFT Q` | Right Shift | Q | -- | Mod-tap: hold=Shift, tap=Q |
| 50 | 4 | Left outer 1 | `&trans` | -- | -- | -- | Inherits Ctrl/Hyper+Z from QWERTY |
| 51 | 4 | Left outer 2 | `&trans` | -- | -- | -- | Inherits Alt/Hyper+B from QWERTY |
| 52 | 4 | Left inner 1 | `&trans` | -- | -- | -- | Inherits GUI/Hyper+A from QWERTY |
| 53 | 4 | Left inner 2 | `&trans` | -- | -- | -- | Inherits Numbers/Esc from QWERTY |
| 54 | 4 | Left inner 3 | `&trans` | -- | -- | -- | Inherits Mouse/Enter from QWERTY |
| 55 | 4 | Right inner 3 | `&lts NUMBERS SPACE` | NUMBERS layer | Space | -- | Layer-tap: hold=Numbers, tap=Space |
| 56 | 4 | Right inner 2 | `&trans` | -- | -- | -- | Inherits Nav/Space from QWERTY |
| 57 | 4 | Right inner 1 | `&mm_hash_dllr` | -- | `#` | `$` | Mod-morph: tap=#, shift=$ |
| 58 | 4 | Right outer 2 | `&mm_fslh_bslh` | -- | `/` | `\` | Mod-morph: tap=/, shift=\ |
| 59 | 4 | Right outer 1 | `&trans` | -- | -- | -- | Inherits Fkeys/Enter from QWERTY |

**Encoder rotation:** Left = `C_VOL_UP` / `C_VOL_DN`, Right = `PG_UP` / `PG_DN`

---

## Design Rationale

### Symbol-First Number Row

Engram's number row inverts the standard US layout: symbols are the base tap and digits require Shift. This reflects that symbols like `|`, `=`, `~`, `+`, `<`, `>`, `^`, `&`, `%`, `*` are used more frequently in programming than their corresponding digits. Each position uses a mod-morph behavior to implement this inversion without requiring a separate symbols layer.

### Custom Punctuation Pairs

Rather than using standard US shifted pairs (e.g., Shift+9 = `(`), Engram groups related punctuation together:
- `,`/`;` and `.`/`:` pair statement terminators with list separators
- `'`/`(` and `"`/`)` pair quotes with their corresponding parenthesis direction
- `?`/`!` pair question with exclamation
- `@`/`` ` `` pair common prefix symbols
- `#`/`$` and `/`/`\` pair related operators on the thumb cluster

### Home Row: B and V on Outer Positions

The BVh ZQl variant places B (pos 24) and V (pos 35) on the outer home row as layer-taps with NAV. This provides:
- NAV layer access on hold from the home row pinkies
- Two common consonants (B, V) on the home row without displacing the CAGS HRM cluster

### Lower Row: Z and Q on Outer Positions

Z (pos 36) and Q (pos 49) occupy the outer lower row as mod-taps with Shift. These are the two least frequent English letters, making them ideal for the hardest-to-reach positions. The Shift hold function preserves modifier access without dedicating a key solely to Shift.

### CAGS Home Row Mods

The inner home row uses CAGS order (Ctrl-Alt-GUI-Shift, pinky to index):
- **Left:** C/Ctrl (25), I/Alt (26), E/GUI (27), A/Shift (28)
- **Right:** H/Shift (31), T/GUI (32), S/Alt (33), N/Ctrl (34)

This places the vowel cluster (I, E, A) on the left hand and the most common consonants (H, T, S, N) on the right, following Engram's design philosophy of balancing hand usage.

### Thumb Cluster

The thumb cluster is mostly inherited from the QWERTY base via `&trans`, with three exceptions:
- **Pos 55:** `&lts NUMBERS SPACE` -- explicit Numbers layer access on hold, Space on tap
- **Pos 57:** `&mm_hash_dllr` -- mod-morph for `#`/`$`, commonly used in programming
- **Pos 58:** `&mm_fslh_bslh` -- mod-morph for `/`/`\`, commonly used in paths and regex

### Position 13: Unused

Position 13 (upper row, second from left) is `&none`. In Engram's layout, the `@` symbol that would typically occupy an alpha position has been moved to position 0 (top-left) as the `&mm_at_grave` mod-morph, leaving this position intentionally blank.

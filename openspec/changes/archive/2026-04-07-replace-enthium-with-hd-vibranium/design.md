## Context

The flash profile currently has: QWERTY(0), Enth+(1), Enthium(2), HD Gold(3). This change replaces Enthium with HD Vibranium on layer 2. HD Vibranium uses linger keys (hold-tap) for all non-standard punctuation pairs and secondary letters (Z on X, Q on W).

## Goals / Non-Goals

**Goals:**
- HD Vibranium on layer 2 with display-name "hd-Vp"
- Linger keys using existing `htk` behavior for all small-char pairs
- H-digraph combos (left-hand, consonant + right neighbor) with title case variants
- R on thumb (pos 53), fat-finger R+Enter(54) → R
- QU combo via linger: W holds Q, so W(14) can be part of a QU combo

**Non-Goals:**
- Not modifying Enth+ or HD Gold layers
- Not modifying `config/sofle.keymap` main keymap (only the profile)

## Decisions

### 1. HD Vibranium Sofle Mapping

```
Row 1 (13-22):
  13: &htk Z X      14: &htk Q W      15: &kp M       16: &kp G       17: &htk EXCL DQT
  18: &htk AT HASH  19: &htk COLON DOT 20: &htk QMARK SQT 21: &kp J    22: &kp B

Home (25-34) with CAGS HRM:
  25: &hml LCTRL S  26: &hml LALT C   27: &hml_g LGUI N 28: &hml LSHFT T 29: &kp K
  30: &htk SEMI COMMA 31: &hmr RSHFT A 32: &hmr_g RGUI E 33: &hmr RALT I 34: &hmr RCTRL H

Bottom (37-41, 44-48):
  37: &kp V  38: &kp P  39: &kp L  40: &kp D  41: &lts MOUSE FSLH (with * linger — need htk+lts combo or just lts)
  44: &htk PLUS MINUS  45: &kp U  46: &kp O  47: &kp Y  48: &kp F

Thumb (50-59):
  53: &kp R  (all others &trans)

Outer columns (12, 23, 24, 35, 36, 49): &trans
Row 0 (0-11): &trans
```

Note: pos 41 has `/*` (tap /, hold *). Since it also needs `&lts MOUSE`, we can't combine htk + lts. Use `&lts MOUSE FSLH` and handle * via a separate combo or just skip the linger on this one key. The `*` is accessible on the QWERTY number row via shift+8. Keep `&lts MOUSE FSLH` for simplicity.

Similarly, pos 30 `,;` needs htk but the QWERTY base has this position as a normal key. Since this is an overlay, `&htk SEMI COMMA` works fine at pos 30.

### 2. H-Digraph Combo Positions (HD Vibranium)

All H-paired consonants are on the left hand. Combos use consonant + right neighbor:

| Digraph | Keys | Positions |
|---------|------|-----------|
| TH | T + K | 28 + 29 |
| SH | S + C | 25 + 26 |
| CH | C + N | 26 + 27 |
| GH | G + " | 16 + 17 |
| PH | P + L | 38 + 39 |
| WH | W + M | 14 + 15 |

Title case: 3-key combos with pos 36 (left shift) and pos 49 (right shift).

### 3. QU Combo

W(14) has Q as its linger (hold). For a QU combo, pressing X(13) + W(14) simultaneously could trigger QU (same positions as other layouts). The combo fires before the htk resolves, so it works.

### 4. R + Enter Fat-Finger

Combo: pos 53 + 54, layers HD_VIB → `&kp R`. Prevents accidental Enter when reaching for R.

### 5. Layer Define and Cycle

- `#define HD_VIB 2` replaces `#define ENTHIUM 2`
- Cycle macro: `enthplus_to_enthium` → `enthplus_to_hd_vib` (bindings: `&tog ENTHPLUS &tog HD_VIB`)
- Cycle macro: `enthium_to_hd_gold` → `hd_vib_to_hd_gold` (bindings: `&tog HD_VIB &tog HD_GOLD`)
- Update all combo/adjust layer references from ENTHIUM to HD_VIB

## Risks / Trade-offs

- **Pos 41 `/*` linger lost** → Can't combine htk with lts MOUSE. User gets `/` with mouse layer-tap, and `*` via shift+8 on number row. Acceptable.
- **Left-hand H-digraph combos** → All consonants on left, so all combos are left-hand. Fine for the user, just different muscle memory from Enth+ right-hand combos.

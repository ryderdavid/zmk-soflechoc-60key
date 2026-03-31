## Context

This change builds on the `add-hd-gold-profile` change. That change creates `profiles/hd-gold.keymap` with HD Gold on layer 3. This change modifies that same profile to:
1. Add H-digraph combos (consonant + right neighbor → consonant+H)
2. Replace layer 1 (Engram) with Enth+ (Enthium variant, right homerow K,T,S,N,H)
3. Retire Engram to `profiles/engram-bvhzql.keymap`

## Goals / Non-Goals

**Goals:**
- H-digraph combos for TH, SH, CH, GH, PH, WH on Enth+ and HD Gold layers
- Enth+ layer with right homerow rearranged: H to pinky, T to index
- Clean removal of Engram from the flash profile (no Engram-specific mod-morphs needed)
- Preserved Engram as a profile for future re-use

**Non-Goals:**
- Not modifying the main `config/sofle.keymap` (still has Engrammer as layer 3, Engram as layer 1)
- Not implementing HD Gold adaptive keys (just combos)
- Not adding H-digraph combos to QWERTY or vanilla Enthium layers

## Decisions

### 1. Enth+ Right Homerow Rearrangement

Current Enthium right homerow (pos 30-34): K, H(RSHFT), T(RGUI), N(RALT), S(RCTRL)
Enth+ right homerow (pos 30-34): K, T(RSHFT), S(RGUI), N(RALT), H(RCTRL)

Changes:
- pos 31: `&hmr RSHFT H` → `&hmr RSHFT T`
- pos 32: `&hmr_g RGUI T` → `&hmr_g RGUI S`
- pos 33: `&hmr RALT N` → `&hmr RALT N` (unchanged)
- pos 34: `&hmr RCTRL S` → `&hmr RCTRL H`

CAGS order preserved: Ctrl(pinky)-Alt(ring)-Gui(middle)-Shift(index).

### 2. H-Digraph Combo Positions

**On Enth+ (layer 1):**

| Digraph | Keys | Positions | Rationale |
|---------|------|-----------|-----------|
| TH | T + S | 31 + 32 | Home row, index + middle (most common digraph, best fingers) |
| SH | S + N | 32 + 33 | Home row, middle + ring |
| CH | C + I | 25 + 26 | Left home, pinky + ring (C is left pinky in Enthium) |
| GH | G + F | 46 + 47 | Bottom row right, G + right neighbor |
| PH | P + Z | 21 + 22 | Top row right, P + right neighbor |
| WH | W + (outer) | 35 + ... | W is at pos 35 (right outer home). Combo with pos 23 (right outer top) or skip — WH is rare |

Note: WH may be impractical on Enth+ since W is in the outer column. Consider skipping or using a different combo. TH and SH are by far the most important.

**On HD Gold (layer 3):**

| Digraph | Keys | Positions | Rationale |
|---------|------|-----------|-----------|
| TH | T + Z | 53 + 41 | Thumb-T (pos 53) + key directly above it (pos 41) — natural thumb+finger chord |
| SH | S + N | 26 + 27 | Left home, S + right neighbor |
| CH | C + L | 38 + 39 | Bottom row left |
| GH | G + M | 14 + 15 | Top row left |
| PH | P + V | 16 + 17 | Top row left |
| WH | W + Z | 40 + 41 | Bottom row left |

### 3. Combo Implementation

Each H-digraph combo uses a ZMK macro that outputs the two letters:

```c
th_digraph: th_digraph {
    compatible = "zmk,behavior-macro";
    #binding-cells = <0>;
    wait-ms = <0>;
    tap-ms = <0>;
    bindings = <&kp T &kp H>;
};
```

Combos are layer-restricted:
- Enth+ combos: `layers = <ENTHPLUS>;`
- HD Gold combos: `layers = <HD_GOLD>;`
- Some combos may share positions across both layers if the same keys are used

Combo timing: `timeout-ms = <30>` (tight window for simultaneous press, avoids accidental triggers during fast typing). This matches the Hands Down recommendation for combos.

### 4. Layer 1 Replacement

- Remove the entire `engram_layer` block and all Engram-specific mod-morphs (`mm_at_grave`, `mm_pipe_n1`, etc.)
- Replace with `enthplus_layer` (display-name "enth+")
- `#define ENGRAM 1` → `#define ENTHPLUS 1`
- Update `layout_to_engram` combo, `engram_to_enthium` macro, adjust layer toggles
- Cycle becomes: QWERTY → Enth+ → Enthium → HD Gold → QWERTY

### 5. Engram Retirement

Save current Engram layer + all its mod-morph behaviors to `profiles/engram-bvhzql.keymap` as a complete keymap snapshot. This file contains the full keymap with Engram on layer 1 so it can be restored later if wanted.

## Risks / Trade-offs

- **Combo timing sensitivity** → Too short a timeout and combos won't trigger reliably; too long and fast same-row rolls misfire. Start with 30ms, tune after testing.
- **WH is rare** → May not be worth a combo. Can add later if needed.
- **Same-position combos on different layers** → ZMK supports layer-restricted combos, so the same physical positions can produce different digraphs on Enth+ vs HD Gold. No conflict.
- **Mod-morph removal** → Engram's custom shifted pairs (mod-morphs) are NOT used by Enth+ or HD Gold. Removing them cleans up the keymap significantly but means the profile can't switch back to Engram without re-adding them.

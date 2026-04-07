## Why

Replace the stock Enthium layer (layer 2) with Hands Down Vibranium ("hd-Vp") in the flash profile. Enthium is kept as a retired profile. HD Vibranium shares the same home row concept as HD Gold but with different letter placement and linger keys for punctuation. Having two HD variants (Vibranium + Gold) alongside Enth+ gives a solid comparison set.

## What Changes

- Replace layer 2 (Enthium) with HD Vibranium (display-name "hd-Vp")
- Retire Enthium to `profiles/enthium.keymap` (already exists, verify)
- HD Vibranium alpha layout with linger keys (hold-tap for small chars):
  - Top: Xz Wq m g "! | #@ .: '? j b
  - Home: s c n t k | ,; a e i h (CAGS HRM)
  - Bottom: v p l d /* | -+ u o y f
  - Thumb: R (pos 53), space falls through from QWERTY
- H-digraph combos for HD Vibranium (consonants on left hand → left-side combos):
  - TH: T(28)+K(29), SH: S(25)+C(26), CH: C(26)+N(27)
  - GH: G(16)+"(17), PH: P(38)+L(39), WH: W(14)+M(15)
- Fat-finger protection: R(53)+Enter(54) → R only
- Update cycle: QWERTY → Enth+ → HD Vibranium → HD Gold → QWERTY
- Update `#define ENTHIUM 2` → `#define HD_VIB 2`, all references

## Capabilities

### New Capabilities
- `hd-vibranium-layer`: HD Vibranium alpha layout on layer 2 with CAGS HRM, linger keys, and H-digraph combos

### Modified Capabilities
- `layout-config`: Layer 2 changes from Enthium to HD Vibranium; cycle toggle chain updated

## Impact

- `profiles/hd-gold.keymap` — layer 2 replaced, defines/macros/combos updated
- `config/sofle.keymap` — synced from profile
- Enthium-specific combos and thumb bindings removed; HD Vibranium combos added
- QU combo on layer 2 changes: uses X(13)+W(14) linger keys (W holds Q, X holds Z → X+W = qu? No — need to check)

## Why

Custom HD Gold variant ("Au+") with personal optimizations: RSNTB left home row, Magic H on thumb, macro lingers (fr/ck/wh), W on right pinky (replacing H), shift keys double as Enter on tap. This is an evolving personal layout to save alongside the standard HD layouts.

## What Changes

- Replace HD Gold (layer 3) with hd-Au+ (display-name "hd-Au+")
- Save current HD Gold as `profiles/hd-gold.keymap`
- Layout changes from Au:
  - Left home: R S N T B (was R S N D B — T replaces D on index)
  - Right home pinky: W instead of H
  - H on thumb (pos 53) as Magic H adaptive key
  - Top row lingers: Jz Gq Mx Pk V
  - Bottom row macro lingers: F/fr, C/ck, W/wh
  - Pos 54: Space (not Enter)
  - Both shift keys (pos 36, 49): hold=shift, tap=enter
- Combos: SH=26+27, CH=38+39, QU=13+14, TH=27+28, N'T=27+40
- Numbers/Mouse layer-tap keys produce Enter on tap

## Capabilities

### New Capabilities
- `hd-au-plus-layer`: Custom HD Gold variant with Magic H, RSNTB home, macro lingers

### Modified Capabilities
- `layout-config`: Layer 3 changes from HD Gold to Au+

## Impact

- `profiles/hd-gold.keymap` — saved profile, layer 3 replaced in active keymap
- New macro hold-tap: `ht_w_wh` for W/WH linger
- Reuses existing `ht_f_fr`, `ht_c_ck`, `ak_h` behaviors

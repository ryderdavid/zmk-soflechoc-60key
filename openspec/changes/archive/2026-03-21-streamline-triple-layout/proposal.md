## Why

The current keymap has 18 layers with accumulated complexity (Gallium, mirrored Enthium, Windows mode variants, caps display layers, word chords). Time to streamline: remove unused layouts and layers, un-mirror Enthium to its original orientation, add Engram BVh ZQl as a third layout option, and simplify the layer stack.

## What Changes

**Remove:**
- Gallium layer and all Gallium-specific layers (GALLIUM, WINMODE_GALLIUM, GALLIUM_CAPS)
- All Gallium word chord combos (`corne-canon-chords.dtsi` — ~2250 lines)
- All Gallium-specific combos (mouse_toggle_g, fatfinger_del_g, fatfinger_bksp_g)
- CAPS_DISPLAY and all caps layers (CAPS_DISPLAY, GALLIUM_CAPS, ENTHIUM_CAPS) — use plain shift instead
- All Windows mode layers (WINMODE, WINMODE_GALLIUM, WINMODE_MOUSE, ENTHIUM_WIN)
- Symbols layer — symbols accessible via number row shifted keys and nav layer
- `td_caps`, `td_shift` tap-dance behaviors (no longer needed without caps toggle)
- `gallium_to_enthium` macro

**Modify:**
- Enthium layer: un-mirror to original Enthium v14 orientation (R on right thumb, vowels on left). Add Space on the far inner right thumb key.
- Cycle toggle combo: QWERTY → Engram → Enthium → QWERTY (replaces Gallium)

**Add:**
- Engram BVh ZQl layout as a toggle overlay layer (display-name "bvhzql")
- Engram-specific combos (mouse toggle, fat-finger protection)
- New cycle toggle macro for Engram→Enthium transition

**Keep unchanged:**
- QWERTY base layer (layer 0)
- Numbers layer
- Nav layer
- Mouse and Precision mouse layers
- Fkeys layer
- Adjust layer (updated toggles)
- All shared behaviors (hml, hmr, hml_g, hmr_g, lts, htk, enter_mash_proof)
- All utility combos (esc, thumb fat-finger, numbers toggle, winmode toggle removed)

## Capabilities

### New Capabilities
- `streamlined-layout`: Simplified layer architecture with QWERTY + Engram + Enthium, reduced from 18 to ~10 layers

### Modified Capabilities
_(none)_

## Impact

- **Layer count**: 18 → ~10 (QWERTY, Engram, Enthium, Numbers, Nav, Numpad, Adjust, Fkeys, Mouse, Prec)
- **Removed files**: `config/corne-canon-chords.dtsi` (or emptied)
- **Modified files**: `config/sofle.keymap` (major restructure)
- **Removed combos**: ~15 Gallium/Windows/caps combos + ~200 word chord combos
- **Simplified behaviors**: remove td_caps, td_shift, caps behavior

## Why

Add Hands Down Gold as a flash profile — a separate firmware image that replaces the Engrammer layer (layer 3) with HD Gold. This gives the user an alternative alpha layout to try without disturbing the main quad-layout firmware. HD Gold is optimized for split keyboards with thumb alphas (T on thumb), very low SFBs, and a high in:out rolling ratio.

## What Changes

- Create a new flash profile `profiles/hd-gold.keymap` based on the current `config/sofle.keymap`
- Replace layer 3 (Engrammer) with Hands Down Gold alpha layout (display-name "hd-Au")
- Update the cycle combo chain: QWERTY → Engram → Enthium → **HD Gold** → QWERTY
- Rename cycle macros and combo labels to reference HD Gold instead of Engrammer
- Update fat-finger protection combos for HD Gold's innermost column keys
- Update the adjust layer toggle from `&tog ENGRAMMER` to `&tog HD_GOLD` (or equivalent define)
- Profile header metadata identifies this as the `hd-gold` profile

## Capabilities

### New Capabilities
- `hd-gold-layer`: Hands Down Gold alpha layout on layer 3 with CAGS home-row mods, adapted to the Sofle 60-key physical layout

### Modified Capabilities
- `layout-config`: Cycle toggle chain updated to include HD Gold instead of Engrammer

## Impact

- `profiles/hd-gold.keymap` — new file (full keymap snapshot)
- No changes to `config/sofle.keymap` (the active keymap stays as-is with Engrammer)
- Build: user flashes this profile by copying it to `config/sofle.keymap` before building, or by adding a separate build matrix entry

## Why

Enthium v14 is an optimized alpha layout that merges Engram 2.0 (left-hand vowels YOU) with Dvorak-style right-hand consonants (HTNS), offering 0.22% effective same-finger bigrams and programming-friendly punctuation placement (HJKL for Vim, `-=` for zooming, `./` for paths). Adding it as a toggle overlay — the same pattern used for Gallium — lets the user trial Enthium without disrupting the existing keymap architecture.

## What Changes

- **New Enthium toggle layer** (layer 1 replacement or new layer index) with Enthium v14 alpha positions mapped to the Sofle 60-key layout, using CAGS home row mods
- **New Enthium caps layer** (conditional: ENTHIUM + CAPS_DISPLAY) with shifted Enthium alpha keys
- **New Enthium + Windows mode layer** (conditional: ENTHIUM + WINMODE) with Ctrl↔GUI swap at the correct CAGS positions
- **New profile** `profiles/enthium.keymap` — complete keymap snapshot with Enthium as the active alpha layout
- **New profile spec** `openspec/specs/profiles/enthium/spec.md` — full binding tables for the Enthium profile
- **Updated combos** — layout-aware combos (mouse toggle, fat-finger protection) need Enthium-specific variants with correct key positions
- **Updated word chords** — if corne-canon-chords.dtsi is layout-aware, Enthium chord positions need generating

## Capabilities

### New Capabilities
- `enthium-profile`: Enthium v14 alpha layout as a Sofle 60-key profile, including the toggle layer, caps layer, Windows mode layer, layout-aware combos, and profile spec

### Modified Capabilities
_(none — the existing corne-canon profile and layout-config platform are unchanged)_

## Impact

- **New files**: `profiles/enthium.keymap`, `openspec/specs/profiles/enthium/spec.md`
- **Modified files**: `config/sofle.keymap` (adds Enthium layers, combos, conditional rules), `config/corne-canon-chords.dtsi` (possibly — Enthium chord positions)
- **Layer count**: increases from 15 to 18 (Enthium alpha + Enthium caps + Enthium win mode)
- **No firmware/hardware changes**: purely keymap configuration
- **Build**: existing CI pipeline builds automatically on push

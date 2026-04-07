## Why

Hands Down layouts use H-digraph combos — pressing a consonant + its right neighbor simultaneously outputs the consonant followed by H (TH, SH, CH, WH, GH, PH). These are among the most common English digraphs, and handling them with combos means H doesn't need a prime homerow position. This unlocks a better Enthium variant ("Enth+") where the right homerow becomes K,T,S,N,H — putting T (the most common consonant) on the index finger instead of H.

## What Changes

- **Create Enth+ layer**: Modified Enthium with right homerow K,T,S,N,H (H moves from index → pinky, T from middle → index, S from pinky → middle). Display-name "enth+"
- **Add H-digraph combos**: Consonant + right-neighbor combos outputting TH, SH, CH, GH, PH, WH — active on Enth+ and HD Gold layers
- **Replace layer 1**: Enth+ takes layer 1 slot (was Engram BVh ZQl "bvhzql")
- **Retire Engram**: Save current Engram layer to `profiles/engram-bvhzql.keymap` before removing from active keymap
- **Update cycle**: QWERTY → Enth+ → Enthium → HD Gold → QWERTY (in the hd-gold flash profile)
- **Update all references**: Defines, combos, macros, adjust layer toggles updated for the new layer 1

## Capabilities

### New Capabilities
- `h-digraph-combos`: Positional combos that output common English H-digraphs (TH, SH, CH, GH, PH, WH) by pressing a consonant key + the key immediately to its right
- `enthium-plus-layer`: Enth+ alpha layout — Enthium variant with right homerow K,T,S,N,H and CAGS HRM

### Modified Capabilities
- `layout-config`: Layer 1 changes from Engram to Enth+; cycle toggle chain updated

## Impact

- `profiles/hd-gold.keymap` — modified (layer 1 becomes Enth+ instead of Engram, H-digraph combos added)
- `profiles/engram-bvhzql.keymap` — new file (retired Engram layer preserved as profile)
- Combos section in keymap gains ~6 new H-digraph combos with layer restrictions
- All Engram-specific mod-morph behaviors can be removed from the profile (Enth+ uses standard shifted pairs like Enthium)

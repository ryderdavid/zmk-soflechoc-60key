## Why

Engrammer is the programmer-friendly variant of Engram — same alpha positions but with standard QWERTY shifted pairs (`,<` `.>` `'"` etc.) instead of Engram's custom remapped pairs. This means no mod-morphs needed, making it simpler and more compatible with standard OS keyboard drivers. Adding it as a 4th alpha layout option completes the Engram family on the board: Engram BVh ZQl (custom shifts) vs Engrammer (standard shifts) vs Enthium (Engram meets Promethium).

## What Changes

- **New Engrammer toggle layer** at index 3 (shifting Numbers to 4, Nav to 5, etc.)
- **No mod-morphs** — Engrammer uses standard QWERTY shifted pairs, so plain `&kp` for all punctuation
- **4-way cycle toggle**: QWERTY → Engram → Enthium → Engrammer → QWERTY
- **New transition macro**: `enthium_to_engrammer` (tog ENTHIUM, tog ENGRAMMER)
- **New transition macro**: `engrammer_to_qwerty` (just tog ENGRAMMER)
- **Layer index shift**: all functional layers (Numbers, Nav, Adjust, Fkeys, Mouse, Prec) shift up by 1
- **Display module update**: layer scan range from 8 to 9, content threshold from >=3 to >=4
- **Engrammer-specific combos**: fat-finger encoder protection

## Capabilities

### New Capabilities
- `engrammer-layout`: Engrammer alpha layout as a toggle overlay with standard shifted pairs and 4-way cycle toggle

### Modified Capabilities
_(none)_

## Impact

- **Layer count**: 9 → 10 (QWERTY=0, ENGRAM=1, ENTHIUM=2, ENGRAMMER=3, NUMBERS=4, NAV=5, ADJUST=6, FKEYS=7, MOUSE=8, PREC=9)
- **Modified files**: `config/sofle.keymap`, `zmk-modules/mod-status/src/nice_view_status.c`
- **All `#define` values** for functional layers shift up by 1
- **All `&lts`/`&mo` references** to functional layers auto-update via `#define` names

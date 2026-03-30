## Context

Current architecture has 9 layers (0-8) with 3 alpha layouts at indices 0-2. Adding Engrammer at index 3 shifts all functional layers up by 1. Since combos and conditional layers use `#define` names, the index shift is handled by updating the `#define` values — no binding changes needed.

## New Layer Architecture

| Index | Define | Display Name | Purpose |
|-------|--------|-------------|---------|
| 0 | QWERTY | qwerty | Base QWERTY with CAGS HRM |
| 1 | ENGRAM | bvhzql | Engram BVh ZQl (custom shifted pairs via mod-morphs) |
| 2 | ENTHIUM | enthium | Enthium v14 (original orientation) |
| 3 | ENGRAMMER | engrmmr | Engrammer (standard shifted pairs, no mod-morphs) |
| 4 | NUMBERS | numbers | Number grid + numpad |
| 5 | NAV | nav | Navigation, arrows |
| 6 | ADJUST | adjust | BT, power, layout toggles (conditional: NAV + NUMBERS) |
| 7 | FKEYS | fkeys | F1-F12, media, utilities |
| 8 | MOUSE | mouse | Mouse movement |
| 9 | PREC | prec | Precision mouse |

## Engrammer Alpha Mapping

```
Engrammer layout (standard Engram alpha positions, programmer punctuation):

Row 1:  b  y  o  u  '"   ;:  l  d  w  v  z
Row 2:  c  i  e  a  ,<   .>  h  t  s  n  q
Row 3:  g  x  j  k  -_   /?  r  m  f  p
```

**Key difference from Engram BVh ZQl**: Engrammer keeps B on the upper row (not home row) and uses standard QWERTY shifted pairs. No mod-morphs needed.

### Sofle position mapping:

**Row 0** (0-11): `&trans` — inherit QWERTY number row

**Row 1** (12-23):
- 12: `&kp TAB`
- 13: `&kp B`
- 14: `&kp Y`
- 15: `&kp O`
- 16: `&kp U`
- 17: `&kp SQT` (standard: shift gives `"`)
- 18: `&kp SEMI` (standard: shift gives `:`)
- 19: `&kp L`
- 20: `&kp D`
- 21: `&kp W`
- 22: `&kp V`
- 23: `&kp Z`

**Row 2 home** (24-35) with CAGS HRM:
- 24: `&lts NAV C` (hold=Nav, tap=C) — note: Engrammer has C at far left
- 25: `&hml LCTRL I`
- 26: `&hml LALT E`
- 27: `&hml_g LGUI A`
- 28: `&hml LSHFT COMMA` — comma with shift=< (standard!)
- 29: `&kp DOT` (standard: shift gives >)
- 30: `&kp H`... wait, Engrammer has `.>` at the inner position.

Actually, looking at the layout more carefully: Engrammer has 11 keys on the home row (c i e a , . h t s n q) for a split with 5+1+1+5 = 12 positions. The inner two keys are `,` and `.`.

Revised home row:
- 24: `&lts NAV C`
- 25: `&hml LCTRL I`
- 26: `&hml LALT E`
- 27: `&hml_g LGUI A`
- 28: `&hml LSHFT COMMA`
- 29: `&kp DOT` (inner left — standard shifted pair `.>`)
- 30: `&kp H` (inner right... no, wait)

Hmm, the Engrammer has `,<` and `.>` as the inner pair on the home row. Let me recount for 6 columns per hand:

Left 6 columns: C I E A , .? No, that's the 5-column split. For 6 columns:
- Col 0 (far left): C
- Col 1: I
- Col 2: E
- Col 3: A
- Col 4: `,<`
- Col 5 (inner): `.>`

Right 6 columns:
- Col 0 (inner): H
- Col 1: T
- Col 2: S
- Col 3: N
- Col 4: Q
- Col 5 (far right): (nothing on standard Engrammer — but Sofle has 6 cols)

Wait, the standard Engrammer layout shows: `c i e a , . h t s n q` which is 11 keys for 2 hands. On a 6-column split:
- Left (6): C I E A , .
- Right (5+1): H T S N Q + ?

That doesn't split evenly. Looking at Sunaku's Glove80 keymap (which IS a split), the split is:
- Left 5: C I E A ,
- Right 5+1: . H T S N Q? No...

Actually for a 34-key board (5 cols per hand), it's:
- Left home: C I E A ,
- Right home: . H T S N

With Q somewhere on the bottom row. For our Sofle (6 cols per hand), positions 24-29 (left) and 30-35 (right):
- 24: C (with Nav hold)
- 25: I (Ctrl)
- 26: E (Alt)
- 27: A (GUI)
- 28: `,<` (Shift) — Shift on comma is unusual but matches the Engram BVh ZQl pattern
- 29: `.>` (plain, inner left)
- 30: H (plain, inner right)
- 31: T (Shift)
- 32: S (GUI)
- 33: N (Alt)
- 34: Q (Ctrl)
- 35: (Nav hold + ?) — Engrammer doesn't have a letter here. Could use `&trans` to inherit SQT from base, or `&none`.

Wait — Engrammer has `q` at the END of the home row. In BVh ZQl, Q is on the bottom row. In standard Engrammer, Q replaces V's home row spot. So:
- 34: `&hmr RCTRL Q`
- 35: `&trans` or `&lts NAV something`

**Row 3 bottom** (36-49):
Left: G X J K -_
Right: /? R M F P

- 36: `&mt LSHFT G` (or just `&kp LSHFT` with G elsewhere... Engrammer has G at bottom-left. Use `&mt LSHFT G` like the BVh ZQl pattern)
- 37: `&kp X`
- 38: `&kp J`
- 39: `&kp K`
- 40: `&kp MINUS` (standard: shift gives _)
- 41: `&kp FSLH` (standard: shift gives ?)... but this was the Mouse position. Use `&lts MOUSE FSLH`? Or remove mouse hold.
- 44: `&kp R`... wait, the right bottom starts with `/?`. Let me check:

Right bottom: /? R M F P
- 44: `&kp FSLH` (/) — but left inner already has FSLH? No, left inner has `-_`. Let me re-read.

The Engrammer bottom row is: `g x j k -_ /? r m f p`
Left 5+1: G X J K - and then the inner column...

For 6 columns per hand:
- Left: G X J K - (5 keys + encoder at 42)
- Right: / R M F P (5 keys + encoder at 43)

Actually the split for 5+5 bottom row with the encoder positions (42, 43) in between:
- 36-41 (left 6): Shift/G, X, J, K, -, Mouse/?  ... hmm
- 44-49 (right 6): R, M, F, P, ?, Shift/something

Let me just keep it simple and follow the same pattern as BVh ZQl:
- 36: `&mt LSHFT G`
- 37: `&kp X`
- 38: `&kp J`
- 39: `&kp K`
- 40: `&kp MINUS`
- 41: `&lts MOUSE FSLH` (Mouse hold + /)
- 44: `&kp R`
- 45: `&kp M`
- 46: `&kp F`
- 47: `&kp P`
- 48: `&trans` (inherit Engram's SQT? Or &none)
- 49: `&trans`

Hmm, Engrammer has `=+` and `\|` on the far right of row 1. For Sofle:
- 22: `&kp V`
- 23: `&kp Z`

But wait, those are upper right columns. Engrammer has: `b y o u ' ; l d w v z =+ \|`. That's 13 keys on row 1 which doesn't fit in 12 positions. For a standard split, the outer keys (`=+`, `\|`) would be on the number row or thumb area.

I think the simplest approach: map the core 10 alpha keys per row (5 left + 5 right) to positions 13-17 and 18-22, with outer positions (12, 23) for tab and whatever fits. Same pattern as existing layouts.

**Thumb row**: all `&trans` to inherit from base, unless Engrammer has specific thumb keys. Engrammer for split keyboards doesn't specify thumbs — those are board-specific.

## 4-Way Cycle Toggle

```
QWERTY ──combo──▶ ENGRAM ──combo──▶ ENTHIUM ──combo──▶ ENGRAMMER ──combo──▶ QWERTY
  (tog ENGRAM)    (engram_to_      (enthium_to_        (tog ENGRAMMER)
                   enthium)         engrammer)
```

4 combos at positions 46+47+48+49, each restricted to the active layout layer:
- `layout_to_engram`: layers=<QWERTY>, `&tog ENGRAM`
- `layout_to_enthium`: layers=<ENGRAM>, `&engram_to_enthium`
- `layout_to_engrammer`: layers=<ENTHIUM>, `&enthium_to_engrammer` macro
- `layout_to_qwerty`: layers=<ENGRAMMER>, `&tog ENGRAMMER`

New macros:
- `enthium_to_engrammer`: `&tog ENTHIUM &tog ENGRAMMER`

The existing `engram_to_enthium` stays.

## Display Module

Update `nice_view_status.c`:
- Layer scan: `for (int i = 9; i >= 0; i--)` (was 8)
- Content threshold: `content >= 4` (was >= 3, since indices 0-3 are now alpha layouts)

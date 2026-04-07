## Context

Pos 37 and 48 are bottom-row outer keys (pinky stretch). Pos 15 and 16 are top-row middle keys (easy reach). Adding the bottom key's letter as a linger on the top key makes those letters accessible without the stretch.

## Goals / Non-Goals

**Goals:**
- Linger on pos 15/16 for each HD layer's pos 37/48 letters
- Fkeys: Cmd+Z/X/C/V on pos 37-40
- BT selectors on left thumb (pos 50-54) in fkeys layer

**Non-Goals:**
- Not changing QWERTY layer
- Not removing existing keys (lingers ADD to existing tap behavior)

## Decisions

### 1. Linger mappings per layer

| Layer | Pos 15 | Pos 16 |
|-------|--------|--------|
| VV | `&htk P M` (was `&kp M`) | `&htk B G` (was `&kp G`) |
| VP | `&htk V M` (was `&kp M`) | `&htk F G` (was `&kp G`) |
| Au | `&htk X M` (was `&kp M`) | `&htk K P` (was `&kp P`) |

### 2. Fkeys bottom-left remap

Current: `&kp LG(V)  &bt BT_SEL 0  &bt BT_SEL 1  &bt BT_SEL 2  &bt BT_SEL 3  &bt BT_SEL 4`
New:     `&kp LG(V)  &kp LG(Z)     &kp LG(X)     &kp LG(C)     &kp LG(V)     ...`

Wait — pos 36 already has `&kp LG(V)`. The user wants pos 37-40 = Cmd+Z/X/C/V. So:
- 36: keep `&kp LG(V)` (or change)
- 37: `&kp LG(Z)` (was `&bt BT_SEL 0`)
- 38: `&kp LG(X)` (was `&bt BT_SEL 1`)
- 39: `&kp LG(C)` (was `&bt BT_SEL 2`)
- 40: `&kp LG(V)` (was `&bt BT_SEL 3`)

### 3. BT selectors → left thumb

Pos 50-54 in fkeys layer: `&bt BT_SEL 0` through `&bt BT_SEL 4`

## Risks / Trade-offs

- Pos 36 already has `&kp LG(V)` and pos 37 gets `&kp LG(Z)` — the full Cmd+ZXCV stack is 36-40 but reversed (V at 36, Z at 37). That's fine — it matches the physical left-to-right order V,Z,X,C,V or the user adjusts.

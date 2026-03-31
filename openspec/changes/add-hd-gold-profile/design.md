## Context

The current keymap (`config/sofle.keymap`) has a quad-layout architecture: QWERTY (0), Engram (1), Enthium (2), Engrammer (3), plus 6 shared functional layers (4-9). A 4-key combo (positions 46-47-48-49) cycles through the four alphas. The user wants a flash profile that swaps Engrammer for Hands Down Gold so they can try it without modifying the main firmware.

Hands Down Gold layout (from Alan Reiser, keyboard-design.com JSON):
```
Top row:    j  g  m  p  v      ;  .  /  "  '
Home row:   r  s  n  d  b      ,  a  e  i  h
Bottom row: x  c  l  w  z      -  u  o  y  k
Thumb:      (T on left thumb — replaces the lower-layer tap on position 53)
```

Key design point: HD Gold puts `T` on a thumb key. On the Sofle 60-key, position 53 (left inner thumb, currently `&lts NUMBERS SPACE` on the base layer but overridden per-layer) is the natural home for thumb-T in the overlay.

## Goals / Non-Goals

**Goals:**
- Create `profiles/hd-gold.keymap` as a complete, flashable keymap snapshot
- Layer 3 is HD Gold with CAGS home-row mods matching the existing `hml`/`hmr` behaviors
- Cycle combo updated: QWERTY → Engram → Enthium → HD Gold → QWERTY
- Fat-finger combos updated for HD Gold's innermost keys (positions 41/42 and 43/44)
- Display name: "hd-Au"

**Non-Goals:**
- Not modifying `config/sofle.keymap` — the active keymap keeps Engrammer
- Not implementing HD Gold adaptive keys or combos (only the base alpha placement)
- Not adding a separate build.yaml entry (user loads profile manually)

## Decisions

### 1. Layer 3 alpha mapping (Sofle 60-key adaptation)

HD Gold's 3×10 grid maps to the Sofle's inner 10 columns (positions 1-4/7-10 per row). Outer columns (0, 5, 6, 11 equivalents) retain the same punctuation/function keys as Engrammer for consistency.

Row mapping:
- Row 1 (pos 13-16, 19-22): `J G M P` / `DOT FSLH DQT SQT` — note `;` moves to pos 18 (right of split), `.` to 19, `/` to 20
- Home row (pos 25-28, 31-34): `R S N D` / `A E I H` with CAGS HRM
- Bottom row (pos 37-40, 45-48): `X C L W` / `U O Y K`

Special positions:
- Pos 17 (left inner top): `V` — Pos 18 (right inner top): `SEMI`
- Pos 29 (left inner home): `B` — Pos 30 (right inner home): `COMMA`
- Pos 41 (left inner bottom): `Z` with `&lts MOUSE` — Pos 44 (right inner bottom): `MINUS`
- Thumb T: pos 53 gets `&kp T` (overriding the base layer's lower-layer-tap)

The `T` on thumb is HD Gold's defining feature. Since layer 3 is a toggle overlay on QWERTY, position 53 in the overlay simply becomes `&kp T`.

### 2. Punctuation placement

Following the same pattern as Engrammer overlay:
- Pos 12: `&kp TAB` (unchanged)
- Pos 23: `&kp Z` → changes to `&kp Z` is not in HD Gold top row; move to bottom. Actually: HD Gold has `z` on bottom-left. Let me reconsider...

HD Gold bottom row is `x c l w z | - u o y k`. The `z` sits at position 40 (5th from left on bottom row). But Sofle bottom row has 7 keys per side (including encoder). Mapping:

```
Pos: 36  37  38  39  40  41  [42]    [43] 44  45  46  47  48  49
     SFT  X   C   L   W   Z|mouse  enc  enc -   U   O   Y   K  SFT
```

### 3. Home-row mods

Use existing `hml`/`hmr` behaviors with CAGS order matching other layouts:
- Left: `R`=Ctrl, `S`=Alt, `N`=Gui, `D`=Shift
- Right: `A`=Shift, `E`=Gui, `I`=Alt, `H`=Ctrl

Wait — CAGS = Ctrl-Alt-Gui-Shift from pinky to index. On the left: pinky=pos25 (R=Ctrl), ring=pos26 (S=Alt), middle=pos27 (N=Gui), index=pos28 (D=Shift). On the right: index=pos31 (A=Shift), middle=pos32 (E=Gui), ring=pos33 (I=Alt), pinky=pos34 (H=Ctrl). This follows the existing convention.

### 4. Profile creation approach

Copy `config/sofle.keymap`, add profile header metadata, replace layer 3 + update all references (defines, combos, macros, adjust layer toggles).

## Risks / Trade-offs

- **T on thumb removes a layer-tap position** → On the overlay, pos 53 becomes `&kp T` instead of a layer access. Since the base QWERTY layer still has `&lts NUMBERS SPACE` there, and the user can reach Numbers via the combo (G+H positions 29+30), this is acceptable.
- **No adaptive keys** → HD Gold's full design relies on adaptive key sequences to reduce SFBs further. This profile only implements the base alpha grid. The user can add adaptives later if they like the layout.
- **Z placement** → HD Gold puts Z on the bottom row (left pinky area). This matches the existing Engrammer placement pattern.

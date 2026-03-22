## 1. Base Layer Changes (affect all profiles)

- [x] 1.1 Change base layer position 54 from `&lts NAV ENTER` to `&lts MOUSE ENTER`
- [x] 1.2 Change base layer position 57 from `&enter_mash_proof RGUI ENTER` to `&kp RGUI`
- [x] 1.3 Update NAV layer (3) position 55: change from `&trans` to `&none` (cross-thumb misfire protection)
- [x] 1.4 Update SYMBOLS layer (4) position 56: change from `&trans` to `&none` (cross-thumb misfire protection)
- [x] 1.5 Find and update ALL layers that explicitly set position 57 to `&enter_mash_proof RGUI ENTER` — change to `&trans` (so they inherit base's `&kp RGUI`). Affected: gallium(1), nav(3), symbols(4), numpad(5), adjust(6), fkeys(7), winmode(10), w+gal(11), win+mse(12)

## 2. Layer Definitions

- [x] 2.1 Add `#define ENTHIUM 15`, `#define ENTHIUM_CAPS 16`, `#define ENTHIUM_WIN 17` to the keymap header
- [x] 2.2 Add conditional layer rule: ENTHIUM + CAPS_DISPLAY → ENTHIUM_CAPS
- [x] 2.3 Add conditional layer rule: ENTHIUM + WINMODE → ENTHIUM_WIN

## 3. Mirrored Enthium Alpha Layer (Layer 15)

- [x] 3.1 Create the `enthium_layer` block (display-name "enthium") with 60 bindings

## 4. Enthium Caps Layer (Layer 16)

- [x] 4.1 Create `enthium_caps_layer` (display-name "enth+cap") with shifted mirrored Enthium alphas, non-alphas `&trans`

## 5. Enthium Windows Mode Layer (Layer 17)

- [x] 5.1 Create `enthium_win_layer` (display-name "enth+win") swapping Ctrl↔GUI on mirrored Enthium home row

## 6. Cycle Toggle

- [x] 6.1 Create `gallium_to_enthium` macro: `&tog GALLIUM` then `&tog ENTHIUM`
- [x] 6.2 Replace single `layout_toggle` combo with three layer-restricted combos at positions 46+47+48+49
- [x] 6.3 Add `&tog ENTHIUM` to adjust layer at an available position

## 7. Enthium-Specific Combos

- [x] 7.1 Add `mouse_toggle_e` combo with appropriate mirrored positions, restricted to ENTHIUM/ENTHIUM_WIN layers
- [x] 7.2 Add `fatfinger_del_e`: positions 41+42, layers ENTHIUM/ENTHIUM_WIN, outputs `&kp J`
- [x] 7.3 Add `fatfinger_bksp_e`: positions 44+43, layers ENTHIUM/ENTHIUM_WIN, outputs `&kp FSLH`

## 8. Validation

- [x] 8.1 Verify ALL layers (including modified ones) have exactly 60 bindings
- [x] 8.2 Render keymap visualization and verify Enthium layer displays correctly

## 9. Profile & Spec

- [x] 9.1 Save keymap as `profiles/enthium.keymap` with metadata header
- [x] 9.2 Create `openspec/specs/profiles/enthium/spec.md` with full binding tables
- [x] 9.3 Update `openspec/specs/profiles/corne-canon/spec.md` to reflect base layer thumb changes

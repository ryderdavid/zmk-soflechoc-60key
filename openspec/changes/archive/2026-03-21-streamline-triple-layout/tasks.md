## 1. Remove Layers and Behaviors

- [ ] 1.1 Remove `#include "corne-canon-chords.dtsi"` and delete or empty the chords file
- [ ] 1.2 Remove all Gallium-related layers: GALLIUM, WINMODE_GALLIUM, GALLIUM_CAPS
- [ ] 1.3 Remove all Windows mode layers: WINMODE, WINMODE_MOUSE, ENTHIUM_WIN
- [ ] 1.4 Remove all caps layers: CAPS_DISPLAY, ENTHIUM_CAPS
- [ ] 1.5 Remove SYMBOLS layer
- [ ] 1.6 Remove NUMPAD layer (merged into NUMBERS)
- [ ] 1.7 Remove behaviors: `td_caps`, `td_shift`, `caps` (caps-word), `gallium_to_enthium` macro, `td_numlk`, `td_mouse` (if mouse layer is accessible via lts only)
- [ ] 1.8 Remove combos: all Gallium combos (mouse_toggle_g, fatfinger_del_g, fatfinger_bksp_g), layout_to_gallium, layout_to_enthium (old), winmode_toggle, shift_caps, numbers_toggle (if not needed)
- [ ] 1.9 Remove all conditional layer rules except the adjust trigger
- [ ] 1.10 Change position 36 from `&td_shift` to `&kp LSHFT` on all layers that used it

## 2. Update Layer Indices

- [ ] 2.1 Rewrite #define block for 9 layers: QWERTY=0, ENGRAM=1, ENTHIUM=2, NUMBERS=3, NAV=4, ADJUST=5, FKEYS=6, MOUSE=7, PREC=8
- [ ] 2.2 Update ADJUST conditional: NAV + NUMBERS → ADJUST (was NAV + SYMBOLS)
- [ ] 2.3 Update all `&lts SYMBOLS ...` and `&lts NUMPAD ...` bindings to use NUMBERS or NAV instead
- [ ] 2.4 Reorder layer blocks in keymap to match new indices

## 3. Add Engram BVh ZQl Layer (Index 1)

- [ ] 3.1 Create `engram_layer` (display-name "bvhzql") with 60 bindings:
  - Row 0: all `&trans`
  - Row 1: `&trans &none &kp Y &kp O &kp U &none` | `&none &kp L &kp D &kp W &none &trans`
  - Row 2: `&lts NAV B &hml LCTRL C &hml LALT I &hml_g LGUI E &hml LSHFT A &trans` | `&trans &hmr RSHFT H &hmr_g RGUI T &hmr RALT S &hmr RCTRL N &lts NAV V`
  - Row 3: `&kp LSHFT &kp Z &kp G &kp X &kp J &lts MOUSE K &trans` | `&trans &kp R &kp M &kp F &kp P &kp Q &trans`
  - Row 4: all `&trans`
- [ ] 3.2 Add Engram-specific combos: mouse_toggle_eng, fatfinger_del_eng, fatfinger_bksp_eng

## 4. Rewrite Enthium Layer (Index 2) — Original Orientation

- [ ] 4.1 Replace mirrored Enthium with original v14 orientation:
  - Row 0: all `&trans`
  - Row 1: `&trans &kp Q &kp Y &kp O &kp U &kp EQUAL` | `&kp X &kp L &kp D &kp P &kp Z &trans`
  - Row 2: `&lts NAV B &hml LCTRL C &hml LALT I &hml_g LGUI A &hml LSHFT E &lts NUMBERS MINUS` | `&lts NUMBERS K &hmr RSHFT H &hmr_g RGUI T &hmr RALT N &hmr RCTRL S &lts NAV W`
  - Row 3: `&kp LSHFT &kp SQT &kp COMMA &kp DOT &kp SEMI &lts MOUSE FSLH &trans` | `&trans &kp J &kp M &kp G &kp F &kp V &mt RSHFT EXCL`
  - Row 4 (thumbs): `&trans &trans &trans &trans &trans` | `&kp SPACE &lts NAV R &trans &trans &trans`

## 5. Update Base Layer Thumbs

- [ ] 5.1 With SYMBOLS and NUMPAD removed, change base pos 53 from `&lts SYMBOLS ENTER` to `&lts NUMBERS ENTER`
- [ ] 5.2 Change base pos 55 from `&lts SYMBOLS ENTER` to `&kp SPACE`
- [ ] 5.3 Verify pos 54 is `&lts MOUSE ENTER` and pos 56 is `&lts NAV SPACE` (already set)

## 6. Cycle Toggle

- [ ] 6.1 Create `engram_to_enthium` macro: `&tog ENGRAM` then `&tog ENTHIUM`
- [ ] 6.2 Update cycle combos at positions 46+47+48+49:
  - `layout_to_engram`: layers=<QWERTY>, action=`&tog ENGRAM`
  - `layout_to_enthium`: layers=<ENGRAM>, action=`&engram_to_enthium`
  - `layout_to_qwerty`: layers=<ENTHIUM>, action=`&tog ENTHIUM`

## 7. Update Adjust Layer

- [ ] 7.1 Replace Gallium/Enthium toggles with Engram/Enthium toggles
- [ ] 7.2 Remove any references to removed layers

## 8. Update Display Module

- [ ] 8.1 Update `nice_view_status.c` layer indices for 9-layer architecture (no overlay layers needed)
- [ ] 8.2 Remove all caps/windows/gallium layer references from display code

## 9. Fkeys Layer Updates

- [ ] 9.1 Add comfort shortcuts to fkeys layer left column: pos 0=`&kp LG(Z)` (undo), pos 12=`&kp LG(X)` (cut), pos 24=`&kp LG(C)` (copy), pos 36=`&kp LG(V)` (paste)
- [ ] 9.2 Add BT profile select to fkeys layer at QWERTY ZXCVB positions: pos 37=`&bt BT_SEL 0`, pos 38=`&bt BT_SEL 1`, pos 39=`&bt BT_SEL 2`, pos 40=`&bt BT_SEL 3`, pos 41=`&bt BT_SEL 4`
- [ ] 9.3 Add `&studio_unlock` to fkeys layer pos 50 (left outermost thumb)

## 10. Validation

- [ ] 9.1 Verify exactly 9 layers, all with 60 bindings
- [ ] 9.2 Verify no references to removed layers (GALLIUM, SYMBOLS, NUMPAD, WINMODE, CAPS_DISPLAY, etc.)
- [ ] 9.3 Build and flash

## 10. Update Specs

- [ ] 10.1 Update `openspec/specs/layout-config/spec.md` for new architecture
- [ ] 10.2 Create or update profile specs for the new layout

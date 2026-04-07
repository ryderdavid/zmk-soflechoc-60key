## 1. Create Profile Base

- [x] 1.1 Copy `config/sofle.keymap` to `profiles/hd-gold.keymap`
- [x] 1.2 Add profile metadata header (Profile: hd-gold, Description, Created date, Based on: engrammer quad-layout)

## 2. Update Defines and Comments

- [x] 2.1 Replace `#define ENGRAMMER 3` with `#define HD_GOLD 3` in the profile
- [x] 2.2 Update file header comment: change "Engrammer" references to "HD Gold" in layer list and cycle description

## 3. Replace Layer 3 Alpha Grid

- [x] 3.1 Replace `engrammer_layer` with `hd_gold_layer` (display-name "hd-Au")
- [x] 3.2 Map HD Gold alphas to Sofle positions with CAGS HRM (`hml`/`hmr`)
- [x] 3.3 Set position 53 (left inner thumb) to `&kp T`
- [x] 3.4 Verify layer has exactly 60 bindings

## 4. Update Cycle Combos and Macros

- [x] 4.1 Rename `enthium_to_engrammer` macro to `enthium_to_hd_gold` (bindings: `&tog ENTHIUM &tog HD_GOLD`)
- [x] 4.2 Update `layout_to_engrammer` combo to reference `enthium_to_hd_gold` and layer HD_GOLD
- [x] 4.3 Update `layout_to_qwerty` combo: `&tog HD_GOLD` on layer HD_GOLD

## 5. Update Fat-Finger Combos

- [x] 5.1 Update `fatfinger_del_engr` for HD Gold: key = `Z`, layer = HD_GOLD
- [x] 5.2 Update `fatfinger_bksp_engr` for HD Gold: key = `MINUS`, layer = HD_GOLD

## 6. Update Adjust Layer

- [x] 6.1 Replace `&tog ENGRAMMER` with `&tog HD_GOLD` in the adjust layer

## 7. Validate and Visualize

- [x] 7.1 Verify the profile keymap parses without errors via `keymap parse`
- [x] 7.2 Generate keymap-drawer YAML/SVG/PNG for the profile (visual check)

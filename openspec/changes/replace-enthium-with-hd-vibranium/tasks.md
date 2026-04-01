## 1. Retire Enthium

- [ ] 1.1 Verify `profiles/enthium.keymap` exists (or save current profile with Enthium as layer 2)
- [ ] 1.2 Remove `enthium_layer` block from the hd-gold profile

## 2. Update Defines

- [ ] 2.1 Replace `#define ENTHIUM 2` with `#define HD_VIB 2`
- [ ] 2.2 Update file header comment: Enthium → HD Vibranium in layer list and cycle description

## 3. Create HD Vibranium Layer

- [ ] 3.1 Create `hd_vib_layer` (display-name "hd-Vp") with linger keys via `htk` and CAGS HRM
- [ ] 3.2 Set pos 53 to `&kp R`
- [ ] 3.3 Verify layer has exactly 60 bindings

## 4. Add H-Digraph Combos for HD Vibranium

- [ ] 4.1 Add lowercase combos: TH(28+29), SH(25+26), CH(26+27), GH(16+17), PH(38+39), WH(14+15) — layers HD_VIB
- [ ] 4.2 Add title case combos with pos 36 (left shift) for all 6 digraphs
- [ ] 4.3 Add title case combos with pos 49 (right shift) for all 6 digraphs

## 5. Add QU and Fat-Finger Combos

- [ ] 5.1 Add QU combo: 13+14 on HD_VIB → qu_lower
- [ ] 5.2 Add QU title case combos: 36+13+14 and 49+13+14 on HD_VIB → qu_title
- [ ] 5.3 Add R fat-finger combo: 53+54 on HD_VIB → &kp R
- [ ] 5.4 Add fat-finger combos: 41+42 → FSLH, 43+44 → MINUS on HD_VIB

## 6. Update Cycle Combos and Macros

- [ ] 6.1 Rename `enthplus_to_enthium` macro → `enthplus_to_hd_vib` (bindings: `&tog ENTHPLUS &tog HD_VIB`)
- [ ] 6.2 Rename `enthium_to_hd_gold` macro → `hd_vib_to_hd_gold` (bindings: `&tog HD_VIB &tog HD_GOLD`)
- [ ] 6.3 Update `layout_to_enthium` combo → `layout_to_hd_vib` (uses new macro, layers ENTHPLUS)
- [ ] 6.4 Update `layout_to_hd_gold` combo to use new macro, layers HD_VIB

## 7. Update Enthium References

- [ ] 7.1 Remove Enthium-specific fat-finger combos (fatfinger_del_e, fatfinger_bksp_e)
- [ ] 7.2 Remove Enthium from QU combo layer list (QWERTY ENTHPLUS ENTHIUM → QWERTY ENTHPLUS)
- [ ] 7.3 Update N'T combo: remove nt_enthium, add nt_hd_vib with correct positions (N(27)+T(28) — wait, that's adjacent! — or T(28)+... need to check)
- [ ] 7.4 Replace `&tog ENTHIUM` with `&tog HD_VIB` in adjust layer

## 8. Validate and Build

- [ ] 8.1 Verify profile parses via `keymap parse`
- [ ] 8.2 Build and flash

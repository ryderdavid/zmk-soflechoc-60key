## 1. Layer Index Update

- [ ] 1.1 Update #define block: insert ENGRAMMER=3, shift NUMBERS→4, NAV→5, ADJUST→6, FKEYS→7, MOUSE→8, PREC→9
- [ ] 1.2 Update ADJUST conditional: NAV + NUMBERS → ADJUST (define names handle this automatically)
- [ ] 1.3 Update display module: scan range 0-9, content threshold >=4

## 2. Create Engrammer Layer (Index 3)

- [ ] 2.1 Create `engrammer_layer` block (display-name "engrmmr") with 60 bindings:
  - Row 0: all `&trans`
  - Row 1: Tab, B, Y, O, U, SQT | SEMI, L, D, W, V, Z
  - Row 2: Nav/C, Ctrl/I, Alt/E, GUI/A, Shift/COMMA, DOT | H, Shift/T... (finalize in implementation from Engrammer reference)
  - Row 3: Shift/G, X, J, K, MINUS, Mouse/FSLH | R, M, F, P, trans, trans
  - Row 4: all `&trans`
- [ ] 2.2 Insert layer block in keymap after Enthium (3rd position in file)

## 3. Cycle Toggle Update

- [ ] 3.1 Create `enthium_to_engrammer` macro: `&tog ENTHIUM &tog ENGRAMMER`
- [ ] 3.2 Update cycle combos to 4-way:
  - `layout_to_engram`: layers=<QWERTY> (unchanged)
  - `layout_to_enthium`: layers=<ENGRAM> (unchanged)
  - `layout_to_engrammer`: layers=<ENTHIUM>, `&enthium_to_engrammer`
  - `layout_to_qwerty`: layers=<ENGRAMMER>, `&tog ENGRAMMER`
- [ ] 3.3 Add `&tog ENGRAMMER` to adjust layer

## 4. Combos

- [ ] 4.1 Add Engrammer fat-finger combos (41+42 and 44+43) with correct letters
- [ ] 4.2 Update existing combos if layer restrictions need updating

## 5. Validation

- [ ] 5.1 Verify exactly 10 layers, all with 60 bindings
- [ ] 5.2 Verify no references to old layer indices
- [ ] 5.3 Build, flash, and test 4-way cycle

## 6. Documentation

- [ ] 6.1 Create `openspec/specs/profiles/engrammer/spec.md`
- [ ] 6.2 Update `openspec/specs/layout-config/spec.md` for 10-layer architecture

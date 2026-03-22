## ADDED Requirements

### Requirement: Engram BVh ZQl alpha toggle layer
The keymap SHALL include an Engram BVh ZQl alpha toggle layer at index 1 (display-name "bvhzql") with CAGS HRM on the home row. B and V on home row, Z and Q on lower row.

#### Scenario: Engram alpha keys
- **WHEN** Engram is active
- **THEN** alpha positions output Engram BVh ZQl letters: home row B C I E A (left) / H T S N V (right), upper Y O U (left) / L D W (right), lower Z G X J K (left) / R M F P Q (right)

### Requirement: Original (non-mirrored) Enthium v14 alpha toggle layer
The keymap SHALL include the original Enthium v14 layout at index 2 (display-name "enthium") — NOT mirrored. Vowels (Y O U, I A E) on the left hand, consonants (L D P, H T N S) on the right. R on a right thumb key. Space on the far inner right thumb.

#### Scenario: Enthium original orientation
- **WHEN** Enthium is active
- **THEN** left hand has vowels (Y O U / I A E) and right hand has consonants (L D P / H T N S), matching the upstream Enthium v14 layout

#### Scenario: R and Space on Enthium thumbs
- **WHEN** Enthium is active
- **THEN** position 55 outputs Space and position 56 outputs R on tap (with Nav on hold)

### Requirement: Three-layout cycle toggle
The layout cycle combo (positions 46+47+48+49) SHALL cycle QWERTY → Engram → Enthium → QWERTY via layer-restricted combos.

#### Scenario: Full cycle
- **WHEN** user presses the 4-key combo three times
- **THEN** the layout transitions from QWERTY to Engram to Enthium and back to QWERTY

### Requirement: Remove Gallium and all variants
The keymap SHALL NOT contain Gallium, WINMODE_GALLIUM, or GALLIUM_CAPS layers. All Gallium-specific combos and word chords SHALL be removed.

#### Scenario: No Gallium artifacts
- **WHEN** the keymap is compiled
- **THEN** no Gallium layer, combo, or word chord definition exists

### Requirement: Remove caps toggle layers
The keymap SHALL NOT contain CAPS_DISPLAY, GALLIUM_CAPS, or ENTHIUM_CAPS layers. The td_caps and td_shift behaviors SHALL be removed. Position 36 SHALL use plain `&kp LSHFT`.

#### Scenario: Plain shift
- **WHEN** user presses position 36
- **THEN** Left Shift is output (no caps toggle behavior)

### Requirement: Remove Windows mode layers
The keymap SHALL NOT contain WINMODE, WINMODE_GALLIUM, WINMODE_MOUSE, or ENTHIUM_WIN layers. The winmode_toggle combo SHALL be removed.

#### Scenario: No Windows mode
- **WHEN** the keymap is compiled
- **THEN** no Windows mode layer or combo exists

### Requirement: Remove Symbols layer
The SYMBOLS layer SHALL be removed. All `&lts SYMBOLS ...` bindings SHALL be changed to use another layer (NUMPAD or NAV) or plain key presses.

#### Scenario: No Symbols layer
- **WHEN** the keymap is compiled
- **THEN** no Symbols layer exists and no binding references SYMBOLS

### Requirement: Adjust layer trigger update
With SYMBOLS removed, the ADJUST conditional layer SHALL activate via NAV + NUMPAD instead of NAV + SYMBOLS.

#### Scenario: Adjust access
- **WHEN** user holds both Nav and Numpad simultaneously
- **THEN** the Adjust layer activates

### Requirement: 10 total layers
The final keymap SHALL have exactly 10 layers: QWERTY(0), ENGRAM(1), ENTHIUM(2), NUMBERS(3), NAV(4), NUMPAD(5), ADJUST(6), FKEYS(7), MOUSE(8), PREC(9).

#### Scenario: Layer count
- **WHEN** the keymap is compiled
- **THEN** exactly 10 layer blocks exist, each with 60 bindings

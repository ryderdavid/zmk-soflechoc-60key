## ADDED Requirements

### Requirement: Engrammer alpha toggle layer
The keymap SHALL include an Engrammer toggle layer at index 3 (display-name "engrmmr") with CAGS HRM on the home row. All punctuation SHALL use standard QWERTY shifted pairs — no mod-morphs.

#### Scenario: Standard shifted pairs
- **WHEN** Engrammer is active and the user types `'` with Shift held
- **THEN** `"` is output (standard QWERTY behavior, not Engram's `(`)

#### Scenario: No mod-morphs
- **WHEN** Engrammer is active
- **THEN** no mod-morph behaviors are used — all keys use plain `&kp`

### Requirement: 4-way cycle toggle
The layout cycle combo (positions 46+47+48+49) SHALL cycle QWERTY → Engram → Enthium → Engrammer → QWERTY.

#### Scenario: Full 4-way cycle
- **WHEN** user presses the 4-key combo four times starting from QWERTY
- **THEN** the layout transitions QWERTY → Engram → Enthium → Engrammer → QWERTY

### Requirement: Layer index shift
All functional layers (NUMBERS, NAV, ADJUST, FKEYS, MOUSE, PREC) SHALL shift up by 1 to accommodate Engrammer at index 3.

#### Scenario: 10 total layers
- **WHEN** the keymap is compiled
- **THEN** exactly 10 layer blocks exist with indices 0-9

### Requirement: Engrammer-specific combos
Fat-finger encoder protection combos SHALL exist for the Engrammer layer.

#### Scenario: Fat-finger protection
- **WHEN** Engrammer is active and the innermost bottom key + encoder are pressed
- **THEN** the Engrammer letter at that position is output

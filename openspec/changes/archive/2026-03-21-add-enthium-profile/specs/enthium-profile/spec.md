## ADDED Requirements

### Requirement: Mirrored Enthium v14 alpha toggle layer
The keymap SHALL include a mirrored Enthium v14 alpha toggle layer where left-hand letters are placed on the right hand and vice versa (same finger, opposite hand). CAGS home row mods SHALL be applied to the inner home row keys (S N T H / E A I C). R SHALL be on the left thumb at position 53 as `&lts SYMBOLS R`.

#### Scenario: Toggle mirrored Enthium on
- **WHEN** the user activates the Enthium toggle
- **THEN** alpha positions output mirrored Enthium v14 letters: left home = S(Ctl) N(Alt) T(Gui) H(Sft), right home = E(Sft) A(Gui) I(Alt) C(Ctl)

#### Scenario: R on left thumb
- **WHEN** Enthium is active and the user taps position 53
- **THEN** the key outputs R; holding position 53 activates the SYMBOLS layer

### Requirement: Base layer thumb changes
The base QWERTY layer SHALL be modified at positions 54 and 57. These changes affect ALL profiles.

#### Scenario: Position 54 provides Mouse layer access
- **WHEN** the user holds position 54 on any profile
- **THEN** the MOUSE layer activates (hold=Mouse, tap=Enter)

#### Scenario: Position 57 is Cmd only
- **WHEN** the user presses position 57 on any profile
- **THEN** only RGUI (Cmd) is output — no Enter on tap, on any layer

### Requirement: Cross-thumb misfire protection
The NAV layer SHALL have `&none` at position 55 and the SYMBOLS layer SHALL have `&none` at position 56 to prevent accidental Enter/Space when holding adjacent layer-tap thumb keys.

#### Scenario: No accidental Enter while in Nav
- **WHEN** the user holds Nav (position 56) and accidentally taps position 55
- **THEN** nothing happens (position 55 is `&none` on the NAV layer)

#### Scenario: No accidental Space while in Symbols
- **WHEN** the user holds Sym (position 55) and accidentally taps position 56
- **THEN** nothing happens (position 56 is `&none` on the SYMBOLS layer)

### Requirement: Cycle toggle between alpha layouts
The layout toggle combo (positions 46+47+48+49) SHALL cycle through QWERTY → Gallium → Enthium → QWERTY using layer-restricted combos.

#### Scenario: Cycle from QWERTY to Gallium
- **WHEN** the user presses the 4-key combo while on QWERTY
- **THEN** Gallium activates

#### Scenario: Cycle from Gallium to Enthium
- **WHEN** the user presses the 4-key combo while on Gallium
- **THEN** Gallium deactivates and Enthium activates

#### Scenario: Cycle from Enthium back to QWERTY
- **WHEN** the user presses the 4-key combo while on Enthium
- **THEN** Enthium deactivates, returning to QWERTY

### Requirement: Enthium caps toggle layer
The keymap SHALL include a conditional layer (ENTHIUM + CAPS_DISPLAY) that sends shifted versions of all mirrored Enthium alpha keys.

#### Scenario: Caps with Enthium active
- **WHEN** both Enthium and CAPS_DISPLAY are active
- **THEN** all mirrored Enthium alpha positions send shifted equivalents

### Requirement: Enthium Windows mode layer
The keymap SHALL include a conditional layer (ENTHIUM + WINMODE) that swaps Ctrl↔GUI on the mirrored Enthium home row CAGS positions (25↔27, 32↔34).

#### Scenario: Windows mode with Enthium
- **WHEN** both Enthium and WINMODE are active
- **THEN** pinky positions swap Ctrl→GUI and middle positions swap GUI→Ctrl

### Requirement: Layout-aware combos for Enthium
The keymap SHALL include Enthium-specific variants of mouse toggle and fat-finger encoder protection combos, restricted to Enthium layers.

#### Scenario: Fat-finger protection
- **WHEN** Enthium is active and position 41 + encoder (42) are pressed simultaneously
- **THEN** J is output (the Enthium letter at position 41), not delete

### Requirement: Existing layer cleanup for position 57
All layers that explicitly set position 57 to `&enter_mash_proof RGUI ENTER` SHALL be changed to `&trans` so they inherit the base layer's `&kp RGUI`.

#### Scenario: Position 57 consistent across layers
- **WHEN** any layer is active
- **THEN** position 57 outputs RGUI (Cmd) with no Enter component

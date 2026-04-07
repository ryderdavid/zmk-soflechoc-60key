## MODIFIED Requirements

### Requirement: Cycle toggle chain includes Enth+ and HD Gold
The 4-key combo (positions 46-47-48-49) SHALL cycle: QWERTY → Enth+ → Enthium → HD Gold → QWERTY. `#define ENGRAM 1` SHALL be replaced with `#define ENTHPLUS 1`. All macros, combos, and adjust-layer toggles referencing ENGRAM SHALL reference ENTHPLUS.

#### Scenario: Cycle from QWERTY to Enth+
- **WHEN** the user presses the cycle combo on QWERTY
- **THEN** Enth+ is toggled on

#### Scenario: Cycle from Enth+ to Enthium
- **WHEN** the user presses the cycle combo on Enth+
- **THEN** Enth+ is toggled off and Enthium is toggled on

#### Scenario: Full cycle returns to QWERTY
- **WHEN** the user presses the cycle combo 4 times starting from QWERTY
- **THEN** the layout returns to QWERTY

### Requirement: Adjust layer toggles updated
The adjust layer SHALL have toggles for Enth+, Enthium, and HD Gold (replacing Engram and Engrammer references).

#### Scenario: Adjust layer shows Enth+ toggle
- **WHEN** the user activates the adjust layer
- **THEN** the position that previously toggled Engram now toggles Enth+

### Requirement: Fat-finger combos for Enth+
Fat-finger protection combos for layer 1 SHALL be updated for Enth+ key positions. Position 41 on Enth+ has `/` (via `&lts MOUSE FSLH`), position 44 has `J`.

#### Scenario: Fat-finger left encoder on Enth+
- **WHEN** the user presses positions 41+42 on the Enth+ layer
- **THEN** the key at position 41 (FSLH) is produced

#### Scenario: Fat-finger right encoder on Enth+
- **WHEN** the user presses positions 43+44 on the Enth+ layer
- **THEN** the key at position 44 (J) is produced

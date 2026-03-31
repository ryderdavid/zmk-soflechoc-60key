## MODIFIED Requirements

### Requirement: Cycle toggle chain includes HD Gold
The 4-key combo (positions 46-47-48-49) SHALL cycle: QWERTY → Engram → Enthium → HD Gold → QWERTY. The `#define ENGRAMMER 3` SHALL be replaced with `#define HD_GOLD 3`. All macros, combos, and adjust-layer toggles referencing ENGRAMMER SHALL reference HD_GOLD.

#### Scenario: Cycle from Enthium to HD Gold
- **WHEN** the user presses the cycle combo (positions 46-47-48-49) while on Enthium
- **THEN** Enthium is toggled off and HD Gold is toggled on

#### Scenario: Cycle from HD Gold back to QWERTY
- **WHEN** the user presses the cycle combo while on HD Gold
- **THEN** HD Gold is toggled off, returning to QWERTY

#### Scenario: Adjust layer has HD Gold toggle
- **WHEN** the user activates the adjust layer
- **THEN** the position that previously toggled Engrammer now toggles HD Gold

### Requirement: Fat-finger protection for HD Gold
The fat-finger combos for layer 3 SHALL produce the correct keys for HD Gold's innermost column: position 41 = Z (so 41+42 combo produces Z), position 44 = MINUS (so 43+44 combo produces MINUS).

#### Scenario: Fat-finger left encoder on HD Gold
- **WHEN** the user accidentally presses positions 41+42 on HD Gold layer
- **THEN** the key at position 41 (Z) is produced

#### Scenario: Fat-finger right encoder on HD Gold
- **WHEN** the user accidentally presses positions 43+44 on HD Gold layer
- **THEN** the key at position 44 (MINUS) is produced

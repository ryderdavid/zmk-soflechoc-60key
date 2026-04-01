## MODIFIED Requirements

### Requirement: Cycle toggle chain includes HD Vibranium
The cycle SHALL be: QWERTY → Enth+ → HD Vibranium → HD Gold → QWERTY. `#define ENTHIUM 2` SHALL be replaced with `#define HD_VIB 2`. All macros, combos, and adjust-layer toggles SHALL reference HD_VIB.

#### Scenario: Cycle from Enth+ to HD Vibranium
- **WHEN** the user presses the cycle combo on Enth+
- **THEN** Enth+ is toggled off and HD Vibranium is toggled on

#### Scenario: Cycle from HD Vibranium to HD Gold
- **WHEN** the user presses the cycle combo on HD Vibranium
- **THEN** HD Vibranium is toggled off and HD Gold is toggled on

### Requirement: Fat-finger combos for HD Vibranium
Layer 2 fat-finger combos SHALL match HD Vibranium's innermost keys. Pos 41 = FSLH (41+42 → FSLH). Pos 44 = MINUS (43+44 → MINUS).

#### Scenario: Fat-finger left encoder on HD Vibranium
- **WHEN** positions 41+42 are pressed on layer 2
- **THEN** FSLH is produced

### Requirement: Enthium retired
Enthium SHALL be preserved in `profiles/enthium.keymap` and removed from the flash profile.

#### Scenario: Enthium profile exists
- **WHEN** the change is implemented
- **THEN** `profiles/enthium.keymap` exists with Enthium on layer 2

## ADDED Requirements

### Requirement: Bottom-row letters as lingers on top-row middle keys
Pos 15 SHALL have pos 37's letter as hold via `htk`. Pos 16 SHALL have pos 48's letter as hold via `htk`. This applies to all three HD layers.

#### Scenario: Hold M on VV produces P
- **WHEN** the user holds pos 15 on HD Vibranium V
- **THEN** P is output (pos 37's letter)

#### Scenario: Hold G on VP produces F
- **WHEN** the user holds pos 16 on HD Vibranium P
- **THEN** F is output (pos 48's letter)

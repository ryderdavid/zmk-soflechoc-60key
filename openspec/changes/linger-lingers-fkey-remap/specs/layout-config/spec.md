## MODIFIED Requirements

### Requirement: Fkeys bottom-left is Cmd+Z/X/C/V
Pos 37-40 on the fkeys layer SHALL be `&kp LG(Z)`, `&kp LG(X)`, `&kp LG(C)`, `&kp LG(V)`.

#### Scenario: Pos 37 on fkeys produces Cmd+Z
- **WHEN** the user presses pos 37 on the fkeys layer
- **THEN** Cmd+Z (undo) is sent

### Requirement: BT selectors on left thumb in fkeys
BT_SEL 0-4 SHALL be on pos 50-54 in the fkeys layer.

#### Scenario: Pos 50 selects BT profile 0
- **WHEN** the user presses pos 50 on the fkeys layer
- **THEN** BT profile 0 is selected

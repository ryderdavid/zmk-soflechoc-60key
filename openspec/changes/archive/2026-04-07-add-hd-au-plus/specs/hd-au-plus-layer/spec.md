## ADDED Requirements

### Requirement: Au+ layout on layer 3
Display-name "hd-Au+". RSNTB left home, CAGS HRM, Magic H on thumb, W on right pinky, macro lingers, shift-tap-enter.

#### Scenario: Layer 3 produces Au+ alphas
- **WHEN** the user activates layer 3
- **THEN** all keys produce Au+ placements as specified

### Requirement: Magic H on thumb
Pos 53 SHALL be `&ak_h` adaptive key (AH→AU, EH→EO, OH→OU, UH→UA).

#### Scenario: Tap H after A outputs U
- **WHEN** the user taps A then quickly taps pos 53
- **THEN** U is output instead of H

### Requirement: Shift-enter outer columns
Pos 36 and 49 SHALL be `&mt LSHFT ENTER` and `&mt RSHFT ENTER`.

#### Scenario: Tap left shift produces Enter
- **WHEN** the user taps pos 36 on Au+
- **THEN** Enter is output

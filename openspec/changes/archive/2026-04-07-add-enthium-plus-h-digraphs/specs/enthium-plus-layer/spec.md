## ADDED Requirements

### Requirement: Enth+ alpha layout on layer 1
The profile keymap SHALL define layer 1 as Enth+ with display-name "enth+". The layout SHALL be identical to Enthium except for the right homerow rearrangement:

```
Enthium right homerow: K  H(RSHFT)  T(RGUI)  N(RALT)  S(RCTRL)
Enth+   right homerow: K  T(RSHFT)  S(RGUI)  N(RALT)  H(RCTRL)
```

All other positions (left hand, top row, bottom row, thumb cluster) SHALL remain identical to Enthium.

#### Scenario: Right homerow has T on index
- **WHEN** the user activates the Enth+ layer
- **THEN** position 31 produces T on tap and RSHFT on hold

#### Scenario: Right homerow has H on pinky
- **WHEN** the user activates the Enth+ layer
- **THEN** position 34 produces H on tap and RCTRL on hold

#### Scenario: Left hand unchanged from Enthium
- **WHEN** the user activates the Enth+ layer
- **THEN** left-hand positions match Enthium exactly (C,I,A,E home row with CAGS)

### Requirement: Enth+ uses standard shifted pairs
Enth+ SHALL NOT use Engram-style mod-morphs for shifted symbols. All keys SHALL use standard ZMK keycodes with their default shifted pairs.

#### Scenario: No mod-morph behaviors on Enth+
- **WHEN** the user holds Shift and presses any key on Enth+
- **THEN** the standard shifted character is produced (e.g., Shift+1 = !, not a custom mod-morph)

### Requirement: Engram retired to profile
The current Engram layer (layer 1, display-name "bvhzql") and all its Engram-specific mod-morph behaviors SHALL be removed from the flash profile keymap. The complete current keymap (with Engram on layer 1) SHALL be saved to `profiles/engram-bvhzql.keymap` with profile metadata header before removal.

#### Scenario: Engram profile preserved
- **WHEN** the change is implemented
- **THEN** `profiles/engram-bvhzql.keymap` exists with the full keymap including Engram on layer 1

#### Scenario: No Engram mod-morphs in flash profile
- **WHEN** the flash profile keymap is parsed
- **THEN** no `mm_*` mod-morph behaviors from Engram are present

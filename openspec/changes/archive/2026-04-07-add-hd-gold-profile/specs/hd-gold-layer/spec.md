## ADDED Requirements

### Requirement: HD Gold alpha layout on layer 3
The profile keymap SHALL define layer 3 as Hands Down Gold with display-name "hd-Au". The alpha grid SHALL match the canonical HD Gold layout:

```
Top:    J  G  M  P  V      ;  .  /  "  '
Home:   R  S  N  D  B      ,  A  E  I  H
Bottom: X  C  L  W  Z      -  U  O  Y  K
Thumb:  T (position 53)
```

#### Scenario: Layer 3 contains HD Gold alphas
- **WHEN** the user activates layer 3 (via cycle combo or toggle)
- **THEN** all 26 alpha keys produce HD Gold letter placements as specified above

#### Scenario: T on left thumb
- **WHEN** the user taps position 53 while layer 3 is active
- **THEN** the key produces `T`

### Requirement: CAGS home-row mods on HD Gold
The home row alpha keys SHALL use `hml`/`hmr` hold-tap behaviors with CAGS (Ctrl-Alt-Gui-Shift) order from pinky to index:

- Left: R=Ctrl, S=Alt, N=Gui, D=Shift
- Right: A=Shift, E=Gui, I=Alt, H=Ctrl

#### Scenario: Home-row mods active on HD Gold
- **WHEN** the user holds a home-row key on layer 3
- **THEN** the corresponding CAGS modifier activates (e.g., hold R = LCTRL)

#### Scenario: Home-row tap produces alpha
- **WHEN** the user taps a home-row key on layer 3
- **THEN** the alpha letter is produced (e.g., tap R = `r`)

### Requirement: Non-alpha positions match Engrammer pattern
Positions outside the 3×10 alpha grid (row 0 number row, outer columns, thumb cluster except pos 53) SHALL use `&trans` to fall through to the QWERTY base layer, matching the existing overlay pattern.

#### Scenario: Number row falls through
- **WHEN** the user presses a number row key (positions 0-11) on layer 3
- **THEN** the QWERTY base layer binding is used

#### Scenario: Thumb cluster falls through except T
- **WHEN** the user presses any thumb key except position 53 on layer 3
- **THEN** the QWERTY base layer binding is used

### Requirement: Profile file format
The profile SHALL be saved as `profiles/hd-gold.keymap` with metadata header per the profiles system convention.

#### Scenario: Profile file exists with metadata
- **WHEN** the profile is created
- **THEN** `profiles/hd-gold.keymap` exists with Profile/Description/Created/Based-on metadata comment

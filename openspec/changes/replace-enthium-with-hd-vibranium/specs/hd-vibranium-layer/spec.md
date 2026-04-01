## ADDED Requirements

### Requirement: HD Vibranium alpha layout on layer 2
Layer 2 SHALL be HD Vibranium with display-name "hd-Vp". The alpha grid:
```
Top:    Xz  Wq  M   G   "!     #@  .:  '?  J   B
Home:   S   C   N   T   K      ,;  A   E   I   H
Bottom: V   P   L   D   /*     -+  U   O   Y   F
Thumb:  R (pos 53)
```

#### Scenario: Layer 2 produces HD Vibranium alphas
- **WHEN** the user activates layer 2
- **THEN** all alpha keys produce HD Vibranium letter placements

### Requirement: Linger keys via hold-tap
Keys with small secondary characters SHALL use `htk` hold-tap: tap = primary, hold = secondary. Linger pairs: X/Z, W/Q, "/!, #/@, ./: , '/ ?, ,/;, -/+.

#### Scenario: Tap X produces X, hold X produces Z
- **WHEN** the user taps pos 13 on layer 2
- **THEN** X is output
- **WHEN** the user holds pos 13 on layer 2
- **THEN** Z is output

### Requirement: CAGS home-row mods
Home row SHALL use `hml`/`hmr` with CAGS order: S=LCTRL, C=LALT, N=LGUI, T=LSHFT | A=RSHFT, E=RGUI, I=RALT, H=RCTRL.

#### Scenario: Hold T activates left shift
- **WHEN** the user holds pos 28 on layer 2
- **THEN** LSHFT is activated

### Requirement: R on thumb with fat-finger protection
Pos 53 SHALL produce R. Pressing pos 53+54 simultaneously SHALL produce R only (not Enter).

#### Scenario: R+Enter fat-finger outputs R
- **WHEN** the user presses positions 53 and 54 simultaneously on layer 2
- **THEN** only R is output

### Requirement: H-digraph combos on HD Vibranium
Combos SHALL output H-digraphs using consonant + right neighbor (left hand):
- TH: 28+29 (T+K), SH: 25+26 (S+C), CH: 26+27 (C+N)
- GH: 16+17 (G+"), PH: 38+39 (P+L), WH: 14+15 (W+M)
With title case 3-key variants using pos 36 and pos 49.

#### Scenario: TH combo on HD Vibranium
- **WHEN** the user presses positions 28 and 29 simultaneously on layer 2
- **THEN** "th" is output

### Requirement: QU combo
Pressing X(13)+W(14) simultaneously on layer 2 SHALL output "qu". With shift (36 or 49) → "Qu".

#### Scenario: QU combo on HD Vibranium
- **WHEN** the user presses positions 13 and 14 simultaneously on layer 2
- **THEN** "qu" is output

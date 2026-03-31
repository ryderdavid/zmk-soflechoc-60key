## ADDED Requirements

### Requirement: H-digraph combo macros
The keymap SHALL define macros for each H-digraph: TH, SH, CH, GH, PH. Each macro SHALL output the consonant letter followed by H in sequence (e.g., `&kp T &kp H`).

#### Scenario: TH macro outputs T then H
- **WHEN** the TH digraph macro is triggered
- **THEN** the keypress sequence T, H is sent to the host

### Requirement: H-digraph combos on Enth+ layer
The keymap SHALL define combos on the Enth+ layer (layer 1) that trigger H-digraph macros when a consonant key and the key immediately to its right are pressed simultaneously:

| Digraph | Positions | Keys |
|---------|-----------|------|
| TH | 31 + 32 | T + S |
| SH | 32 + 33 | S + N |
| CH | 25 + 26 | C + I |
| GH | 46 + 47 | G + F |
| PH | 21 + 22 | P + Z |

Each combo SHALL be restricted to `layers = <ENTHPLUS>`.

#### Scenario: TH combo on Enth+
- **WHEN** the user presses positions 31 and 32 simultaneously on the Enth+ layer
- **THEN** the output is "th" (or "TH" if shift is active)

#### Scenario: Combo does not fire on other layers
- **WHEN** the user presses positions 31 and 32 simultaneously on the QWERTY layer
- **THEN** the normal individual key bindings fire (no digraph)

### Requirement: H-digraph combos on HD Gold layer
The keymap SHALL define combos on the HD Gold layer (layer 3) that trigger H-digraph macros:

| Digraph | Positions | Keys |
|---------|-----------|------|
| TH | 53 + 41 | T (thumb) + Z (key directly above thumb-T) |
| SH | 26 + 27 | S + N |
| CH | 38 + 39 | C + L |
| GH | 14 + 15 | G + M |
| PH | 16 + 17 | P + V |
| WH | 40 + 41 | W + Z |

Each combo SHALL be restricted to `layers = <HD_GOLD>`.

#### Scenario: TH combo on HD Gold
- **WHEN** the user presses positions 53 (thumb T) and 41 (key above) simultaneously on the HD Gold layer
- **THEN** the output is "th"

### Requirement: Combo timeout
All H-digraph combos SHALL use `timeout-ms = <30>` to require near-simultaneous keypresses and avoid misfires during fast typing.

#### Scenario: Sequential presses do not trigger combo
- **WHEN** the user presses position 31, waits 50ms, then presses position 32 on Enth+
- **THEN** the individual keys fire (T then S), not the TH digraph

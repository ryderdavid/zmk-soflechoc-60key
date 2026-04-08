## Decisions

### Row swap mapping

VF^ swaps the inner alpha keys between rows 1 and 3:

| VF pos | VF binding | VF^ pos | Notes |
|--------|-----------|---------|-------|
| 13 | htk Z X | 37 | |
| 14 | htk Q W | 38 | |
| 15 | htk B M | 39 | |
| 16 | htk F G | 40 | |
| 17 | kp J | 41 | VF^ keeps lts MOUSE, tap=J |
| 18 | htk AT HASH | 18 | STAYS — #@ keeps top position |
| 19 | htk COLON DOT | 45 | |
| 20 | htk ASTRK FSLH | 46 | |
| 21 | htk EXCL DQT | 47 | |
| 22 | htk QMARK SQT | 48 | |
| 37 | kp F | 13 | |
| 38 | kp P | 14 | |
| 39 | kp L | 15 | |
| 40 | kp D | 16 | |
| 41 | lts MOUSE V | 17 | VF^ top: just kp V |
| 44 | htk PLUS MINUS | 44 | STAYS — -+ keeps bottom position |
| 45 | kp U | 19 | |
| 46 | kp O | 20 | |
| 47 | kp Y | 21 | |
| 48 | kp B | 22 | |

### Combo position updates for VF^

VF combos with their VF^ equivalents (top↔bottom row mapping):
- TH: 27+28 → same (home row, unchanged)
- SH: 25+26 → same
- CH: 26+27 → same
- GH: 16+17 → 40+41 (G moves to bottom)
- WH: 14+15 → 38+39 (W moves to bottom)
- QU: 13+14 → 37+38 (X+W move to bottom)
- N'T: 27+40 → 27+16 (D moves to top, but N stays home)
- T'S: 28+25 → same (home row)

### Cycle

QWERTY → VF → VF^ → Pm → Au+ → Enth-M → QWERTY (6 stops)
Insert after VF: macro vf_to_vf_inv (tog VF, tog VF_INV)
VF^ to Pm: macro vf_inv_to_pm (tog VF_INV, tog PM)

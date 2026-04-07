## Context

Replacing HD Gold (layer 3) with user's custom Au+ variant. Reuses existing behaviors (ht_f_fr, ht_c_ck, ak_h from Promethium).

## Goals / Non-Goals

**Goals:**
- Au+ on layer 3 with all specified key placements and combos
- Magic H on thumb via existing ak_h adaptive key
- Macro lingers: F→fr, C→ck, W→wh
- Shift-tap-enter on outer columns

**Non-Goals:**
- Not modifying other layers (VF, Promethium)
- Not changing the Numbers/Nav/Mouse layer content (only the layer-tap keys on Au+)

## Decisions

### 1. Au+ Sofle Mapping

```
Row 0: &trans (all 12)
Row 1: 12:&trans 13:&htk Z J 14:&htk Q G 15:&htk X M 16:&htk K P 17:&kp V
        18-22: same punct lingers as Au (;: .& /* "? '!)  23:&trans
Row 2: 24:&trans 25:&hml LCTRL R 26:&hml LALT S 27:&hml_g LGUI N 28:&hml LSHFT T 29:&kp B
        30:htk PIPE COMMA 31:&hmr RSHFT A 32:&hmr_g RGUI E 33:&hmr RALT I 34:&hmr RCTRL W  35:&trans
Row 3: 36:&mt LSHFT ENTER 37:&ht_f_fr 0 F 38:&ht_c_ck 0 C 39:&kp L 40:&kp D
        41:&ht_w_wh 0 W 42:&trans 43:&trans
        44:&htk PLUS MINUS 45:&kp U 46:&kp O 47:&kp Y 48:&kp K 49:&mt RSHFT ENTER
Row 4: 50-52:&trans 53:&ak_h 54:&kp SPACE 55-59:&trans
```

### 2. New behavior: ht_w_wh

```c
ht_w_wh: ht_w_wh {
    compatible = "zmk,behavior-hold-tap";
    #binding-cells = <2>;
    flavor = "balanced";
    tapping-term-ms = <200>;
    quick-tap-ms = <175>;
    bindings = <&wh_lower>, <&kp>;
};
```
Usage: `&ht_w_wh 0 W`

### 3. Combos

| Combo | Keys | Positions |
|-------|------|-----------|
| SH | S+N | 26+27 |
| CH | C+L | 38+39 |
| QU | J+G | 13+14 |
| TH | N+T | 27+28 |
| N'T | N+D | 27+40 |

Plus title case variants with pos 36/49 (shift keys).

### 4. Right side punct

Same as current HD Gold lingers: ;:(18), .&(19) wait no — Au uses htk lingers now:
- 18: &htk COLON SEMI
- 19: &htk AMPS DOT
- 20: &htk ASTRK FSLH
- 21: &htk QMARK DQT
- 22: &htk EXCL SQT
- 30: &htk PIPE COMMA

### 5. Shift-enter keys

Pos 36 and 49: `&mt LSHFT ENTER` and `&mt RSHFT ENTER`
Hold = shift modifier, tap = enter key.

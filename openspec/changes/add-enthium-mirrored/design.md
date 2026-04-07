## Context

Enthium mirrored swaps left/right hands maintaining finger-to-key mapping.

## Decisions

### Layout mapping
```
Top:    Z(13) P(14) D(15) L(16) X(17)    =(18) U(19) O(20) Y(21) Q(22)
Home:   S(25) N(26) T(27) H(28) K(29)    -(30) E(31) A(32) I(33) C(34)
Bottom: V(37) F(38) G(39) M(40) J(41)    /(44) ;(45) .(46) ,(47) '(48)
Thumb:  R(53)                              ␣(falls through)
```

CAGS HRM: S=LCTRL, N=LALT, T=LGUI, H=LSHFT | E=RSHFT, A=RGUI, I=RALT, C=RCTRL

### Cycle update
Au+ → Enth-M → QWERTY (new final leg before returning to QWERTY)

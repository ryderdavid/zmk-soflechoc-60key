# ZMK Behaviors Reference

Quick reference for all ZMK behaviors relevant to the Sofle Choc 60-key.

---

## Key Press (`&kp`)

Press and release a single keycode.

```
&kp A          // Types 'a' (lowercase)
&kp LSHFT      // Holds left shift
&kp N1         // Types '1'
&kp C_VOL_UP   // Volume up (media key)
```

---

## Mod-Tap (`&mt`)

Hold for modifier, tap for key.

```
&mt LSHFT A    // Hold = Left Shift, Tap = A
&mt LCTRL ESC  // Hold = Left Control, Tap = Escape
&mt RALT SPACE // Hold = Right Alt, Tap = Space
```

**Timing**: Default tapping-term is 200ms. Keys held longer than this activate the modifier.

---

## Layer-Tap (`&lt`)

Hold to activate layer, tap for key.

```
&lt 1 SPACE    // Hold = Layer 1, Tap = Space
&lt 2 BSPC     // Hold = Layer 2, Tap = Backspace
&lt LOWER TAB  // Hold = LOWER layer, Tap = Tab
```

---

## Momentary Layer (`&mo`)

Activate a layer while held.

```
&mo 1          // Activate layer 1 while held
&mo LOWER      // Activate LOWER layer while held
```

---

## Toggle Layer (`&tog`)

Tap to toggle a layer on/off.

```
&tog 1         // Toggle layer 1
&tog RAISE     // Toggle RAISE layer
```

---

## Sticky Layer (`&sl`)

Activate layer for just the next keypress.

```
&sl 1          // Next keypress comes from layer 1
```

---

## Sticky Key (`&sk`)

Apply modifier to just the next keypress.

```
&sk LSHFT      // Next keypress is shifted
&sk LCTRL      // Next keypress has Control
```

---

## Transparent (`&trans`)

Falls through to the same position on the layer below.

```
&trans         // Use whatever the layer below has
```

---

## None (`&none`)

No action. Blocks fallthrough.

```
&none          // Key does nothing
```

---

## Grave-Escape (`&gresc`)

Tap = Escape, Shift+Tap = Grave (`` ` ``).

```
&gresc         // ESC normally, ` with Shift held
```

---

## Caps Word (`&caps_word`)

Activates caps mode that auto-deactivates after non-alpha keys (except `-`, `_`, `BSPC`).

```
&caps_word     // Smart caps lock
```

Custom definition in this keymap extends continue-list:
```
caps: caps {
    compatible = "zmk,behavior-caps-word";
    continue-list = <POUND MINUS BACKSPACE UNDERSCORE>;
};
```

---

## Key Repeat (`&key_repeat`)

Repeats the last pressed key.

```
&key_repeat    // Press again = last key
```

---

## Bluetooth (`&bt`)

Bluetooth profile management.

```
&bt BT_CLR         // Clear current profile
&bt BT_CLR_ALL     // Clear all profiles
&bt BT_SEL 0       // Select profile 0 (0-4)
&bt BT_SEL 1       // Select profile 1
&bt BT_NXT         // Next profile
&bt BT_PRV         // Previous profile
```

---

## External Power (`&ext_power`)

Control external power rail (for displays, LEDs).

```
&ext_power EP_TOG   // Toggle power
&ext_power EP_ON    // Power on
&ext_power EP_OFF   // Power off
```

---

## Studio Unlock (`&studio_unlock`)

Unlock ZMK Studio for real-time keymap editing over USB.

```
&studio_unlock     // Unlock Studio
```

---

## Encoder Bindings (`&inc_dec_kp`)

Encoders use `sensor-bindings` (not regular `bindings`).

```
sensor-bindings = <&inc_dec_kp C_VOL_UP C_VOL_DN &inc_dec_kp PG_UP PG_DN>;
//                 ^^^^^^^^^ left encoder ^^^^^    ^^^^^^^^ right encoder ^^^
//                 clockwise   counter-cw          clockwise   counter-cw
```

Common encoder uses:
```
&inc_dec_kp C_VOL_UP C_VOL_DN       // Volume
&inc_dec_kp PG_UP PG_DN             // Page scroll
&inc_dec_kp UP_ARROW DOWN_ARROW     // Arrow up/down
&inc_dec_kp LEFT_ARROW RIGHT_ARROW  // Arrow left/right
&inc_dec_kp C_BRI_UP C_BRI_DN       // Brightness
&inc_dec_kp C_NEXT C_PREV           // Media next/prev
```

---

## Combos

Press multiple keys simultaneously to trigger a different action.

```c
combos {
    compatible = "zmk,combos";

    combo_name {
        bindings = <&kp KEYCODE>;    // What happens
        key-positions = <POS1 POS2>; // Which keys (position numbers)
        timeout-ms = <50>;           // Optional: time window (default 50ms)
        layers = <0 1>;              // Optional: only on these layers
    };
};
```

### Current combos in this keymap:
| Name | Positions | Action |
|------|-----------|--------|
| backspace | 31, 32 | `&kp BACKSPACE` |
| delete | 27, 33 | `&kp DELETE` |
| esc | 25, 41 | `&kp ESCAPE` |

---

## Conditional Layers

Activate a layer when two other layers are both active.

```c
conditional_layers {
    compatible = "zmk,conditional-layers";

    adjust_layer {
        if-layers = <LOWER RAISE>;   // When both are active
        then-layer = <ADJUST>;       // Activate this layer
    };
};
```

This keymap: holding LOWER + RAISE activates ADJUST.

---

## Macros

Define a sequence of keypresses as a single binding.

```c
macros {
    email_macro: email_macro {
        compatible = "zmk,behavior-macro";
        #binding-cells = <0>;
        bindings = <&kp M &kp E &kp AT &kp E &kp X &kp DOT &kp C &kp O &kp M>;
    };
};
```

Usage: `&email_macro` in a binding position.

### Macro with modifiers:
```c
select_all: select_all {
    compatible = "zmk,behavior-macro";
    #binding-cells = <0>;
    bindings = <&macro_press &kp LGUI>, <&macro_tap &kp A>, <&macro_release &kp LGUI>;
};
```

---

## Required Includes

Different behaviors require different header includes:

| Behavior | Required Include |
|----------|-----------------|
| `&kp`, `&mt`, `&lt`, `&mo`, etc. | `<behaviors.dtsi>`, `<dt-bindings/zmk/keys.h>` |
| `&bt` | `<dt-bindings/zmk/bt.h>` |
| `&ext_power` | `<dt-bindings/zmk/ext_power.h>` |
| `&pointing` | `<dt-bindings/zmk/pointing.h>` |

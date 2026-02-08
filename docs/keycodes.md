# ZMK Keycodes Reference

Complete keycode table for ZMK. Use these with `&kp KEYCODE`.

---

## Letters

| Key | ZMK Code |
|-----|----------|
| A-Z | `A` through `Z` |

All letters are uppercase in ZMK syntax but output lowercase by default. Use `LSHFT` modifier for uppercase.

---

## Numbers

| Key | ZMK Code | Alias |
|-----|----------|-------|
| 1 | `N1` | `NUMBER_1` |
| 2 | `N2` | `NUMBER_2` |
| 3 | `N3` | `NUMBER_3` |
| 4 | `N4` | `NUMBER_4` |
| 5 | `N5` | `NUMBER_5` |
| 6 | `N6` | `NUMBER_6` |
| 7 | `N7` | `NUMBER_7` |
| 8 | `N8` | `NUMBER_8` |
| 9 | `N9` | `NUMBER_9` |
| 0 | `N0` | `NUMBER_0` |

---

## Modifiers

| Key | ZMK Code | Aliases |
|-----|----------|---------|
| Left Shift | `LSHFT` | `LEFT_SHIFT`, `LSHIFT` |
| Right Shift | `RSHFT` | `RIGHT_SHIFT`, `RSHIFT` |
| Left Control | `LCTRL` | `LEFT_CONTROL`, `LCTL` |
| Right Control | `RCTRL` | `RIGHT_CONTROL`, `RCTL` |
| Left Alt | `LALT` | `LEFT_ALT` |
| Right Alt | `RALT` | `RIGHT_ALT` |
| Left GUI | `LGUI` | `LEFT_GUI`, `LWIN`, `LCMD`, `LEFT_COMMAND`, `LEFT_WIN` |
| Right GUI | `RGUI` | `RIGHT_GUI`, `RWIN`, `RCMD`, `RIGHT_COMMAND`, `RIGHT_WIN` |

---

## Punctuation & Symbols

| Symbol | ZMK Code | Aliases |
|--------|----------|---------|
| `-` | `MINUS` | `KP_MINUS` |
| `=` | `EQUAL` | `EQUALS` |
| `[` | `LBKT` | `LEFT_BRACKET` |
| `]` | `RBKT` | `RIGHT_BRACKET` |
| `\` | `BSLH` | `BACKSLASH`, `NON_US_BACKSLASH` |
| `;` | `SEMI` | `SEMICOLON` |
| `'` | `SQT` | `SINGLE_QUOTE`, `APOSTROPHE`, `APOS` |
| `` ` `` | `GRAVE` | `TILDE2` |
| `,` | `COMMA` | |
| `.` | `DOT` | `PERIOD` |
| `/` | `FSLH` | `SLASH`, `FORWARD_SLASH` |

### Shifted Symbols (use with `&kp`)

| Symbol | ZMK Code | Aliases |
|--------|----------|---------|
| `!` | `EXCL` | `EXCLAMATION` |
| `@` | `AT` | `AT_SIGN` |
| `#` | `HASH` | `POUND` |
| `$` | `DLLR` | `DOLLAR` |
| `%` | `PRCNT` | `PERCENT` |
| `^` | `CARET` | |
| `&` | `AMPS` | `AMPERSAND` |
| `*` | `ASTRK` | `ASTERISK`, `STAR` |
| `(` | `LPAR` | `LEFT_PARENTHESIS` |
| `)` | `RPAR` | `RIGHT_PARENTHESIS` |
| `_` | `UNDER` | `UNDERSCORE` |
| `+` | `PLUS` | |
| `{` | `LBRC` | `LEFT_BRACE` |
| `}` | `RBRC` | `RIGHT_BRACE` |
| `\|` | `PIPE` | |
| `~` | `TILDE` | |
| `:` | `COLON` | |
| `"` | `DQT` | `DOUBLE_QUOTES` |
| `<` | `LT` | `LESS_THAN` |
| `>` | `GT` | `GREATER_THAN` |
| `?` | `QMARK` | `QUESTION` |

---

## Navigation

| Key | ZMK Code | Aliases |
|-----|----------|---------|
| Up Arrow | `UP` | `UP_ARROW` |
| Down Arrow | `DOWN` | `DOWN_ARROW` |
| Left Arrow | `LEFT` | `LEFT_ARROW` |
| Right Arrow | `RIGHT` | `RIGHT_ARROW` |
| Home | `HOME` | |
| End | `END` | |
| Page Up | `PG_UP` | `PAGE_UP` |
| Page Down | `PG_DN` | `PAGE_DOWN` |

---

## Editing

| Key | ZMK Code | Aliases |
|-----|----------|---------|
| Backspace | `BSPC` | `BACKSPACE` |
| Delete | `DEL` | `DELETE` |
| Enter | `RET` | `ENTER`, `RETURN` |
| Tab | `TAB` | |
| Space | `SPACE` | |
| Insert | `INS` | `INSERT` |

---

## Function Keys

| Key | ZMK Code |
|-----|----------|
| F1-F12 | `F1` through `F12` |
| F13-F24 | `F13` through `F24` |

---

## System Keys

| Key | ZMK Code | Aliases |
|-----|----------|---------|
| Escape | `ESC` | `ESCAPE` |
| Caps Lock | `CLCK` | `CAPS`, `CAPSLOCK` |
| Print Screen | `PSCRN` | `PRINTSCREEN` |
| Scroll Lock | `SLCK` | `SCROLL_LOCK` |
| Pause/Break | `PAUSE_BREAK` | |
| Context Menu | `K_CMENU` | `K_APP`, `K_CONTEXT_MENU` |

---

## Media & Consumer Keys

| Function | ZMK Code | Aliases |
|----------|----------|---------|
| Volume Up | `C_VOL_UP` | `C_VOLUME_UP` |
| Volume Down | `C_VOL_DN` | `C_VOLUME_DOWN` |
| Mute | `C_MUTE` | |
| Play/Pause | `C_PP` | `C_PLAY_PAUSE` |
| Next Track | `C_NEXT` | |
| Previous Track | `C_PREV` | |
| Stop | `C_STOP` | |
| Brightness Up | `C_BRI_UP` | `C_BRIGHTNESS_INC` |
| Brightness Down | `C_BRI_DN` | `C_BRIGHTNESS_DEC` |

---

## Numpad Keys

| Key | ZMK Code |
|-----|----------|
| Num Lock | `KP_NLCK` or `KP_NUM` |
| Numpad 0-9 | `KP_N0` through `KP_N9` |
| Numpad + | `KP_PLUS` |
| Numpad - | `KP_MINUS` |
| Numpad * | `KP_MULTIPLY` or `KP_ASTERISK` |
| Numpad / | `KP_DIVIDE` or `KP_SLASH` |
| Numpad . | `KP_DOT` |
| Numpad Enter | `KP_ENTER` |

---

## OS Shortcuts (for macros)

Common shortcuts you might want to build macros for:

| Action | macOS | Windows/Linux |
|--------|-------|---------------|
| Copy | `LGUI + C` | `LCTRL + C` |
| Paste | `LGUI + V` | `LCTRL + V` |
| Cut | `LGUI + X` | `LCTRL + X` |
| Undo | `LGUI + Z` | `LCTRL + Z` |
| Redo | `LGUI + LSHFT + Z` | `LCTRL + Y` |
| Select All | `LGUI + A` | `LCTRL + A` |
| Save | `LGUI + S` | `LCTRL + S` |
| Find | `LGUI + F` | `LCTRL + F` |

ZMK also provides platform shortcuts:
- `K_UNDO`, `K_CUT`, `K_COPY`, `K_PASTE` (OS-independent, but support varies)

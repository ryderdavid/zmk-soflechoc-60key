# Somethium QMK → Sofle ZMK Port

Branch: `port/somethium`  
Source: [HandsDownSomethium36](https://github.com/ryderdavid/HandsDownSomethium36) (QMK, 36-key Corne)  
Target: [zmk-soflechoc-60key](config/sofle.keymap) (ZMK, 60-key Sofle Choc)

## Position mapping (36 → 60)

Corne/Somethium uses `LAYOUT_split_3x5_3` (18 keys/half). Mapped to Sofle inner columns + inner thumbs:

| Somethium (per half) | Sofle positions (L / R) |
|----------------------|-------------------------|
| Row 0 keys 0–4 | 12–16 / 18–22 |
| Row 1 keys 5–9 | 24–28 / 30–34 |
| Row 2 keys 10–14 | 36–40 / 44–48 |
| Thumb 0–2 | 52–54 / 55–57 |

**Expansion (24 extra keys):**

| Sofle region | Use |
|--------------|-----|
| Row 0 (0–11) | Number row `1`–`0`, outer `Esc`/`Grave`/`Bspc`/`Del` |
| Outer col L (0,5,12,17,24,29,36,41) | `[` `]` `(` `)` `\` `Tab` |
| Outer col R (6,11,18,23,30,35,44,49) | `-` `=` `;` `'` `!` `?` |
| Encoders 42, 43 | Vol / Page (sensor) |
| Outer thumbs 50,51 / 58,59 | `LSHFT`, `RSHFT` |

## Parity status

| Feature | QMK | ZMK status | Notes |
|---------|-----|------------|-------|
| HDP base layer | `_HDP` | ported | Layer `SOMETHIUM` |
| QWERTY toggle | `TG_BASE` combo | ported | Combo UOY+J / M,.+Slash |
| NAV layer | `_NAV` | ported | Mac shortcuts default; WIN layer for Ctrl |
| SYM layer | `_SYM` | ported | Layer `SYM` |
| NUM layer | `_NUM` | ported | Layer `NUM` + number row |
| MOUSE layer | `_MOUSE` | ported | Emulation only (no touchpad) |
| FKEYS layer | `_FKEYS` | ported | Layer `FKEYS` |
| Home row mods | HDP SNTH… | ported | `hml`/`hmr`/`lts` |
| Linger LTH_* | 20 keys | partial | Hold-taps on inner keys; outers dedicated |
| Combos (~42) | QMK combos | ported | Position-translated |
| Digraph macros | KC_TH, etc. | ported | Existing `_lower`/`_title` macros |
| Sentence autocap | `SENT_AUTO` | ported | Sticky shift combos (`.`/`!`/`?` + space) + toggle on ADJUST |
| Magic comma | post_process | ported | Adaptive + SM |
| Double-comma caps | caps_word_on | ported | Combo + `&caps_word` |
| Capital I | space+i | ported | State machine |
| Single-prior magic | tap history | ported | `zmk-adaptive-key` |
| Multi-key rolls | 8-deep history | partial | High-value SM chains + combos |
| win_mode | runtime flag | changed-feel | `WIN` overlay + conditional Mac/Win NAV |
| App/window cycle | MY_APP_* | ported | `zmk-tri-state` swapper on NAV |
| Secret phrase | KC_SECRET | ported | Macro (empty default; build arg optional) |
| OLED status | oled_task | ported | mod-status widget |
| Touchpad/TrackPoint | pointing | dropped | No hardware |

## Layer indices

| Index | Name |
|-------|------|
| 0 | SOMETHIUM |
| 1 | QWERTY |
| 2 | NAV |
| 3 | SYM |
| 4 | NUM |
| 5 | FKEYS |
| 6 | MOUSE |
| 7 | WIN |
| 8 | ADJUST |
| 9+ | SM state layers (transparent, in `somethium-sm.dtsi`) |

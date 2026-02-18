# nice!view: Show Active Modifiers on Display

**Status:** Open
**Created:** 2026-02-18
**Effort:** Medium (embedded C, ~100–150 lines + boilerplate)
**Type:** Enhancement / Custom ZMK Module

---

## Summary

Add a custom ZMK display widget that shows currently held modifier keys on the left half's nice!view display. The goal is to surface modifier state (Shift, Ctrl, Alt/Opt, Cmd/GUI) visually while they are held — useful both for debugging home row mod activations and for general awareness of modifier state.

---

## Background

The nice!view on the left half currently shows:
- Active layer name
- Battery level
- Bluetooth connection status

ZMK does not ship a modifier-state widget out of the box, but the infrastructure exists:
- `zmk_hid_get_explicit_mods()` (`zmk/hid.h`) returns the current bitmask of held modifiers
- The `keycode_state_changed` event fires on the ZMK event bus whenever a key (including modifiers) is pressed or released
- The nice!view widget framework is extensible via custom ZMK modules placed in `config/`

Home row mod (HRM / hold-tap) activations **do** show up here — once the hold resolves and ZMK sends the modifier to the HID layer, `zmk_hid_get_explicit_mods()` reflects it.

The left half is the central (host-connected) in this build, so full modifier state is available on the half that has the display. No split-peripheral access issues.

---

## Proposed Implementation

### Module location

```
config/
└── widgets/
    ├── mod_status.c        # Widget implementation
    ├── mod_status.h        # Public header (optional)
    ├── CMakeLists.txt      # Add mod_status.c to build
    └── Kconfig             # CONFIG_ZMK_WIDGET_MOD_STATUS toggle
```

The module gets pulled into the build via `sofle.conf` or the shield overlay — no changes to zmk-firmware upstream required.

### Logic outline (mod_status.c)

```c
// 1. Subscribe to keycode_state_changed events
// 2. On each event, check if keycode is a modifier (IS_MOD macro or explicit list)
// 3. Call zmk_hid_get_explicit_mods() to get current bitmask
// 4. Map bitmask bits to symbols:
//      MOD_LSFT | MOD_RSFT  →  ⇧
//      MOD_LCTL | MOD_RCTL  →  ⌃
//      MOD_LALT | MOD_RALT  →  ⌥
//      MOD_LGUI | MOD_RGUI  →  ⌘
// 5. Update an LVGL label widget with the active symbol string
// 6. Clear the label when bitmask == 0
```

> **Note — split keyboard architecture:** This widget runs exclusively on the **left half (central)**. The right half (peripheral) only transmits raw key position numbers over the BLE split link; all keymap processing, behavior resolution, and HID modifier state tracking happen on the central after it receives those positions. `keycode_state_changed` therefore fires only on the central, and `zmk_hid_get_explicit_mods()` is only meaningful there. No additional inter-half BLE traffic is introduced by this widget. The module should be conditioned on `IS_ENABLED(CONFIG_ZMK_DISPLAY)` or the shield's display Kconfig to ensure it does not compile into the peripheral (right half) build.

### Display placement

A small label row beneath the layer name, e.g.:

```
┌─────────────────┐
│ gallium         │  ← layer name (existing)
│ ⌘ ⇧            │  ← modifier row (new, blank when no mods held)
│ ▓▓▓░ BT1       │  ← battery / BT (existing)
└─────────────────┘
```

If screen real estate is tight, modifiers can replace or sit inline with the layer name row when active.

---

## Key ZMK References

| Symbol | Header | Notes |
|--------|--------|-------|
| `zmk_hid_get_explicit_mods()` | `zmk/hid.h` | Returns `zmk_mod_flags_t` bitmask |
| `keycode_state_changed` | `zmk/events/keycode_state_changed.h` | Event to subscribe to |
| `ZMK_LISTENER` / `ZMK_SUBSCRIPTION` | `zmk/event_manager.h` | Event bus wiring macros |
| `MOD_LSFT`, `MOD_LGUI`, etc. | `zmk/modifiers.h` | Modifier bitmask constants |
| Existing widget example | `zmk-firmware/app/boards/shields/nice_view/widgets/` | Reference implementation for layer/battery |

---

## Out of Scope

- Showing modifier state on the right half (no display in this build)
- Showing tap-key state (only modifiers: Shift, Ctrl, Alt, GUI)
- Showing sticky key (`&sk`) state — could be a follow-on

---

## Acceptance Criteria

- [ ] When a modifier is physically held (or HRM hold resolves), the corresponding symbol appears on the display within one display refresh cycle
- [ ] When all modifiers are released, the symbol row clears
- [ ] Multiple simultaneous modifiers all display (e.g. Cmd+Shift shows `⌘ ⇧`)
- [ ] No impact on typing performance or BLE latency
- [ ] Widget is gated behind a `Kconfig` option so it can be disabled cleanly
- [ ] Left-hand and right-hand variants of the same modifier (e.g. LSHFT + RSHFT) deduplicate to a single symbol

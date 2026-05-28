# Change: Port Hands Down Somethium (QMK 36-key) to Sofle ZMK

## Why

Unify the secondary Sofle Choc 60-key with the primary Somethium QMK layout and feature set (HDP, combos, magic typing, NAV/SYM/NUM).

## What Changes

- **BREAKING**: Replaces hd-gold quad-layout (QWERTY + HD Vib-F + HD Prom + HD Au+) with **Somethium** base + **QWERTY** toggle.
- Adds `config/somethium-sm.dtsi` (sentence cap, cap-I, adaptive magic, leader sequences).
- Adds `config/somethium-combos.dtsi` (42+ combos mapped to Sofle positions).
- Extends `config/west.yml` with urob modules: leader-key, tri-state, auto-layer, helpers.
- WIN overlay layer replaces runtime `win_mode` (Mac default NAV, hold WIN combo for Ctrl shortcuts).
- Touchpad/TrackPoint features from QMK are not ported (no hardware).

## Impact

- Affected specs: `layout-config`
- Affected code: `config/sofle.keymap`, `config/sofle.conf`, `config/west.yml`, `docs/somethium-port.md`, `profiles/somethium.keymap`

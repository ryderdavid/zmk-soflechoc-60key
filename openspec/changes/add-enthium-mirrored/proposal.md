## Why

Mirror Enthium left-over-right to create a vowels-on-right variant. This puts EAIC on the right home row and SNTHK on the left — similar to Promethium's consonant arrangement but with Enthium's letter choices.

## What Changes

- Add Enthium Mirrored as layer 10 (display-name "enth-M")
- Update cycle: QWERTY → VF → Pm → Au+ → Enth-M → QWERTY (5 stops)
- Add new cycle macro: au_plus_to_enth_m (tog Au+, tog ENTH_M)
- Update layout_to_qwerty combo to fire from ENTH_M layer

## Capabilities

### New Capabilities
- `enthium-mirrored-layer`: Enthium layout mirrored for vowels-on-right

### Modified Capabilities
- `layout-config`: 5-way cycle, new layer define

## Impact

- New layer 10 added to keymap
- Cycle macros updated for 5 alpha layers
- `#define ENTH_M 10` added

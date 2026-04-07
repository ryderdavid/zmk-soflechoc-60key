## Why

Bottom-row outer keys (pos 37, 48) are harder to reach than top-row middle keys (pos 15, 16). Adding the bottom-row letter as a linger on the corresponding top-row key gives an easier alternative without removing any existing keys. Separately, the fkeys layer needs Cmd+Z/X/C/V on the bottom-left (pos 37-40) for quick undo/cut/copy/paste, which displaces the BT selectors to the left thumb row.

## What Changes

- **Linger additions on all HD layers**: pos 15 gets pos 37's letter as hold, pos 16 gets pos 48's letter as hold
  - VV: M→hold P, G→hold B
  - VP: M→hold V, G→hold F
  - Au: M→hold X, P→hold K
- **Fkeys layer**: pos 37-40 become Cmd+Z, Cmd+X, Cmd+C, Cmd+V (were BT_SEL 0-3 + BT_SEL 4)
- **Fkeys layer**: BT_SEL 0-4 move to pos 50-54 (left thumb row)

## Capabilities

### New Capabilities
- `bottom-row-lingers`: Bottom-row outer letters accessible as lingers on top-row middle keys

### Modified Capabilities
- `layout-config`: Fkeys layer bottom-left remapped to Cmd+Z/X/C/V, BT selectors on thumb

## Impact

- `profiles/hd-gold.keymap` — 3 HD layer edits (pos 15, 16) + fkeys layer edit
- `config/sofle.keymap` — synced

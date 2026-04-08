## 1. Add layer

- [ ] 1.1 Add `#define HD_VF_INV 11`
- [ ] 1.2 Create hd_vf_inv_layer with swapped rows
- [ ] 1.3 Verify 60 bindings

## 2. Update cycle

- [ ] 2.1 Add macros: vf_to_vf_inv, vf_inv_to_hd_prom
- [ ] 2.2 Update cycle combos: VF → VF^ → Pm

## 3. Add combos

- [ ] 3.1 Duplicate VF combos with updated positions for VF^
- [ ] 3.2 Add fat-finger combos for VF^

## 4. Validate and build

- [ ] 4.1 Parse and push

## 1. Retire Engram

- [x] 1.1 Save current `config/sofle.keymap` (which has Engram on layer 1) as `profiles/engram-bvhzql.keymap` with profile metadata header
- [x] 1.2 In the hd-gold profile, remove the `engram_layer` block (layer 1)
- [x] 1.3 Remove all Engram-specific mod-morph behaviors (`mm_at_grave`, `mm_pipe_n1`, `mm_equal_n2`, `mm_tilde_n3`, `mm_plus_n4`, `mm_lt_n5`, `mm_gt_n6`, `mm_caret_n7`, `mm_amps_n8`, `mm_prcnt_n9`, `mm_astrk_n0`, `mm_sqt_lpar`, `mm_dqt_rpar`, `mm_comma_semi`, `mm_dot_colon`, `mm_qmark_excl`, `mm_hash_dllr`, `mm_fslh_bslh`)

## 2. Create Enth+ Layer

- [x] 2.1 Add `#define ENTHPLUS 1` (replacing `#define ENGRAM 1`)
- [x] 2.2 Create `enthplus_layer` block (display-name "enth+") — copy Enthium and swap right homerow: T(31/RSHFT), S(32/RGUI), N(33/RALT), H(34/RCTRL)
- [x] 2.3 Verify Enth+ layer has exactly 60 bindings

## 3. Add H-Digraph Macros

- [x] 3.1 Create macros: `th_digraph`, `sh_digraph`, `ch_digraph`, `gh_digraph`, `ph_digraph`, `wh_digraph` — each outputs consonant + H

## 4. Add H-Digraph Combos for Enth+

- [x] 4.1 Add combo: TH → positions 31+32, layers ENTHPLUS, timeout 30ms
- [x] 4.2 Add combo: SH → positions 32+33, layers ENTHPLUS, timeout 30ms
- [x] 4.3 Add combo: CH → positions 25+26, layers ENTHPLUS, timeout 30ms
- [x] 4.4 Add combo: GH → positions 46+47, layers ENTHPLUS, timeout 30ms
- [x] 4.5 Add combo: PH → positions 21+22, layers ENTHPLUS, timeout 30ms

## 5. Add H-Digraph Combos for HD Gold

- [x] 5.1 Add combo: TH → positions 53+41, layers HD_GOLD, timeout 30ms
- [x] 5.2 Add combo: SH → positions 26+27, layers HD_GOLD, timeout 30ms
- [x] 5.3 Add combo: CH → positions 38+39, layers HD_GOLD, timeout 30ms
- [x] 5.4 Add combo: GH → positions 14+15, layers HD_GOLD, timeout 30ms
- [x] 5.5 Add combo: PH → positions 16+17, layers HD_GOLD, timeout 30ms
- [x] 5.6 Add combo: WH → positions 40+41, layers HD_GOLD, timeout 30ms

## 6. Update Cycle Combos and Macros

- [x] 6.1 Rename `layout_to_engram` combo → `layout_to_enthplus` (bindings: `&tog ENTHPLUS`, layers: QWERTY)
- [x] 6.2 Rename `engram_to_enthium` macro → `enthplus_to_enthium` (bindings: `&tog ENTHPLUS &tog ENTHIUM`)
- [x] 6.3 Update `layout_to_enthium` combo to use `&enthplus_to_enthium`
- [x] 6.4 Update file header comment with new cycle description

## 7. Update Fat-Finger Combos

- [x] 7.1 Update `fatfinger_del_eng` → layer ENTHPLUS, key FSLH (pos 41 on Enth+)
- [x] 7.2 Update `fatfinger_bksp_eng` → layer ENTHPLUS, key J (pos 44 on Enth+)

## 8. Update Adjust Layer

- [x] 8.1 Replace `&tog ENGRAM` with `&tog ENTHPLUS` in adjust layer

## 9. Validate and Visualize

- [x] 9.1 Verify profile keymap parses without errors via `keymap parse`
- [x] 9.2 Generate keymap-drawer YAML/SVG/PNG for the profile

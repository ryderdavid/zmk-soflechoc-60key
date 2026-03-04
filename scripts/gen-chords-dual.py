#!/usr/bin/env python3
"""Generate ZMK chord combos for the corne-canon dual-layout profile.

Produces profiles/corne-canon-chords.dtsi with macros and combos for both
QWERTY (layer 0) and Gallium v1 (layer 1) layouts on the Sofle 60-key.

Each chord is one or more letter keys pressed simultaneously with a space key.
QWERTY combos use layers = <0>; Gallium combos use layers = <1>.

Usage:
    python3 scripts/gen-chords-dual.py          # generate profiles/corne-canon-chords.dtsi
    python3 scripts/gen-chords-dual.py --dry    # print to stdout without writing

Edit the CHORDS list below to add, remove, or modify word chords.
The existing scripts/gen-chords.py is NOT modified — it serves the main keymap.
"""

import sys
from pathlib import Path

# ── QWERTY letter → key position on Sofle 60-key ────────────────────
# Row 1 (CORNE row 0): positions 12-23
# Row 2 (CORNE row 1): positions 24-35
# Row 3 (CORNE row 2): positions 36-41 (left), 44-49 (right) [42,43 = encoders]
QWERTY_POS = {
    "q": 13, "w": 14, "e": 15, "r": 16, "t": 17,
    "y": 18, "u": 19, "i": 20, "o": 21, "p": 22,
    "a": 25, "s": 26, "d": 27, "f": 28, "g": 29,
    "h": 30, "j": 31, "k": 32, "l": 33,
    "z": 37, "x": 38, "c": 39, "v": 40, "b": 41,
    "n": 44, "m": 45,
}

# ── Gallium v1 letter → key position on Sofle 60-key ────────────────
# Same physical matrix, different letter assignment.
# NOTE: Gallium v1 bottom-left is Q X (not X Q like v2)
GALLIUM_V1_POS = {
    "b": 13, "l": 14, "d": 15, "c": 16, "v": 17,
    "j": 18, "y": 19, "o": 20, "u": 21,
    "n": 25, "r": 26, "t": 27, "s": 28, "g": 29,
    "p": 30, "h": 31, "a": 32, "e": 33, "i": 34,
    "q": 37, "x": 38, "m": 39, "w": 40, "z": 41,
    "k": 44, "f": 45,
}

# Thumb space keys (right inner, right middle — both tap to Space)
SPACE_L = 55  # Nav/Space
SPACE_R = 56  # Sym/Space

# Combo timeout — all chord keys must be pressed within this window (ms)
COMBO_TIMEOUT = 50

# ── Chord definitions (50 words, matching full CORNE set) ───────────
# Each entry: (word, [chord_keys])
# The chord fires when all chord_keys + a space key are pressed together.
CHORDS = [
    ("the",   ["t", "h"]),
    ("be",    ["b", "e"]),
    ("to",    ["t", "o"]),
    ("and",   ["a", "n"]),
    ("of",    ["o", "f"]),
    ("in",    ["i", "n"]),
    ("have",  ["h", "v"]),
    ("that",  ["t", "h", "a"]),
    ("for",   ["f", "r"]),
    ("not",   ["n", "t"]),
    ("with",  ["w", "i"]),
    ("you",   ["y", "o"]),
    ("this",  ["t", "i"]),
    ("from",  ["f", "r", "o"]),
    ("but",   ["b", "u"]),
    ("what",  ["w", "a"]),
    ("it",    ["i", "t"]),
    ("he",    ["h", "e"]),
    ("on",    ["o", "n"]),
    ("are",   ["a", "r"]),
    ("do",    ["d", "o"]),
    ("his",   ["h", "i"]),
    ("by",    ["b", "y"]),
    ("they",  ["t", "y"]),
    ("her",   ["h", "r"]),
    ("or",    ["o", "r"]),
    ("at",    ["a", "t"]),
    ("one",   ["o", "e"]),
    ("had",   ["h", "d"]),
    ("say",   ["s", "y"]),
    ("she",   ["s", "h"]),
    ("all",   ["a", "l"]),
    ("which", ["w", "h"]),
    ("will",  ["w", "l"]),
    ("would", ["w", "d"]),
    ("there", ["t", "r"]),
    ("their", ["t", "e", "i"]),
    ("my",    ["m", "y"]),
    ("out",   ["o", "u"]),
    ("up",    ["u", "p"]),
    ("about", ["a", "b"]),
    ("who",   ["w", "o"]),
    ("get",   ["g", "e"]),
    ("make",  ["m", "k"]),
    ("go",    ["g", "o"]),
    ("like",  ["l", "k"]),
    ("just",  ["j", "u"]),
    ("know",  ["k", "n"]),
    ("take",  ["t", "k"]),
    ("come",  ["c", "m"]),
    ("can",   ["c", "a"]),
    ("has",   ["h", "a"]),
    ("any",   ["n", "y"]),
    ("those", ["t", "h", "o"]),
    ("why",   ["w", "y"]),
    ("when",  ["w", "n"]),
    ("won't", ["w", "t"]),
    ("could", ["c", "d"]),
    ("should",["s", "d"]),
    ("might", ["m", "h"]),
    ("can't", ["c", "n"]),
    ("yes",   ["y", "h"]),
    ("no",    ["n", "q"]),
]


# ── Code generation ──────────────────────────────────────────────────
def zmk_keys(word: str) -> str:
    """Convert a word to ZMK &kp bindings."""
    mapping = {"'": "SQT"}
    return " ".join(f"&kp {mapping.get(ch, ch.upper())}" for ch in word)


def gen_macro(name: str, word: str) -> str:
    return (
        f"        wm_{name}: wm_{name} {{\n"
        f"            compatible = \"zmk,behavior-macro\";\n"
        f"            #binding-cells = <0>;\n"
        f"            wait-ms = <0>;\n"
        f"            tap-ms = <0>;\n"
        f"            bindings = <{zmk_keys(word)} &kp SPACE>;\n"
        f"        }};"
    )


def gen_combo(name: str, positions: list[int], space_pos: int,
              suffix: str, layer: str) -> str:
    all_pos = sorted(positions + [space_pos])
    pos_str = " ".join(str(p) for p in all_pos)
    return (
        f"        chord_{name}_{suffix} {{\n"
        f"            bindings = <&wm_{name}>;\n"
        f"            key-positions = <{pos_str}>;\n"
        f"            timeout-ms = <{COMBO_TIMEOUT}>;\n"
        f"            layers = <{layer}>;\n"
        f"        }};"
    )


def generate_dtsi() -> str:
    macros = []
    combos = []
    seen_positions: dict[str, tuple[str, str]] = {}  # "layout:pos_set" → (word, layout)
    skipped = []

    for word, keys in CHORDS:
        name = word.replace("'", "_")
        macros.append(gen_macro(name, word))

        # QWERTY combos (layer 0)
        q_positions = [QWERTY_POS[k] for k in keys]
        for space_pos, sfx in [(SPACE_L, "ql"), (SPACE_R, "qr")]:
            pos_key = f"q:{tuple(sorted(q_positions + [space_pos]))}"
            if pos_key in seen_positions:
                skipped.append(
                    f"  SKIP {word} ({sfx}): same positions as "
                    f"{seen_positions[pos_key][0]} ({seen_positions[pos_key][1]})"
                )
                continue
            seen_positions[pos_key] = (word, sfx)
            combos.append(gen_combo(name, q_positions, space_pos, sfx, "0 10"))

        # Gallium v1 combos (layer 1 + winmode_gallium 11)
        g_positions = [GALLIUM_V1_POS[k] for k in keys]
        for space_pos, sfx in [(SPACE_L, "gl"), (SPACE_R, "gr")]:
            pos_key = f"g:{tuple(sorted(g_positions + [space_pos]))}"
            if pos_key in seen_positions:
                skipped.append(
                    f"  SKIP {word} ({sfx}): same positions as "
                    f"{seen_positions[pos_key][0]} ({seen_positions[pos_key][1]})"
                )
                continue
            seen_positions[pos_key] = (word, sfx)
            combos.append(gen_combo(name, g_positions, space_pos, sfx, "1 11"))

    if skipped:
        print("Position conflicts (first definition wins):", file=sys.stderr)
        for s in skipped:
            print(s, file=sys.stderr)

    return (
        "/* Auto-generated by scripts/gen-chords-dual.py — do not edit by hand */\n"
        "/* CORNE-canonical dual-layout chords: 50 words × 2 layouts × 2 space keys */\n"
        "\n"
        "/ {\n"
        "    macros {\n"
        + "\n\n".join(macros) + "\n"
        "    };\n"
        "\n"
        "    combos {\n"
        "        compatible = \"zmk,combos\";\n"
        "\n"
        + "\n\n".join(combos) + "\n"
        "    };\n"
        "};\n"
    )


def main():
    dtsi = generate_dtsi()

    if "--dry" in sys.argv:
        print(dtsi)
        # Summary stats
        combo_count = dtsi.count("chord_")
        macro_count = dtsi.count("wm_") // 2  # each macro name appears twice (label + ref)
        print(f"\n// {macro_count} macros, {combo_count} combos", file=sys.stderr)
        return

    out = Path(__file__).resolve().parent.parent / "config" / "corne-canon-chords.dtsi"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(dtsi)

    combo_count = dtsi.count("key-positions")
    print(f"Generated {out.relative_to(out.parent.parent)}")
    print(f"  {len(CHORDS)} words, {combo_count} combos")


if __name__ == "__main__":
    main()

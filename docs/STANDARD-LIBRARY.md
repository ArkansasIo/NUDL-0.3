# NUDL 0.3 Standard Library — Initial Contract

This is a proposed API contract. It records the browser IDE's existing built-ins and the intended cross-implementation behavior; it does not imply that every function exists in the native runtime.

## Core functions

| Function | Purpose | Proposed behavior |
|---|---|---|
| `print(value...)` | Write values to program output | Converts each argument using NUDL display formatting |
| `len(value)` | Count elements | Supports text, arrays, and records when implemented |
| `str(value)` | Convert to display text | Deterministic representation |
| `typeof(value)` | Inspect runtime value category | Returns a documented type label |
| `average(values)` | Arithmetic mean | Empty input behavior must be consistent; IDE currently returns zero |

## Math namespace

Proposed functions: `math.abs`, `math.sqrt`, `math.pow`, `math.floor`, `math.ceil`, `math.round`, `math.min`, and `math.max`.

Implementations must document invalid domains, non-finite results, empty argument lists, and numeric conversion behavior.

## Regex namespace

The browser interpreter currently exposes `regex.is_match(pattern, text)` and `regex.replace(pattern, text, replacement)`. Regex syntax and escaping follow the host runtime in the current IDE implementation; portable cross-runtime semantics are not yet frozen.

## Collections and data functions (planned)

- Safe array mapping, filtering, and reduction.
- Record field inspection and schema validation.
- JSON and CSV import/export through explicit APIs.
- Stable sorting with explicit comparison semantics.

## Portability rule

A built-in must not be considered portable merely because one implementation supports it. The conformance suite should test output, errors, argument counts, null handling, and numeric edge cases in both the C++ and TypeScript runtimes.

# NUDL 0.3 Type System — Proposal

This document describes the intended type model. It is a design contract, not a claim that every type is implemented in the current native compiler.

## Primitive types

| Type | Meaning | Proposed literal / example |
|---|---|---|
| `bool` | Boolean value | `true`, `false` |
| `i8`, `i16`, `i32`, `i64` | Signed fixed-width integer | `42` |
| `u8`, `u16`, `u32`, `u64` | Unsigned fixed-width integer | `42` |
| `f32`, `f64` | IEEE-style floating point | `3.5` |
| `text` / `string` | Unicode text | `"hello"` |
| `bytes` | Opaque byte sequence | library-created value |
| `null` | Absence of a value | `null` |
| `void` | No returned value | function return type |

Exact overflow, encoding, and floating-point rules must be fixed by a future conformance release. Implementations must not silently narrow integers or coerce invalid data without an explicit conversion.

## Composite types

- `T[]`: ordered array of values of type `T`.
- Named records: values with explicitly named fields.
- `schema Name { ... }`: record contract with field types, required markers, and defaults.
- Nullable values and maps are planned; their exact syntax is not yet normative.

## Inference and declarations

`let` introduces a reassignable binding; `const` introduces a binding that cannot be reassigned. An optional type annotation states the expected type:

```nudl
let count: i64 = 3
const title: text = "NUDL"
```

The implementation must distinguish a binding's immutability from mutability of objects referenced by the binding. The current compiler subset may not yet enforce all of these rules.

## Type checking goals

1. Every expression has a known or explicitly dynamic type.
2. Function arguments are checked against parameter types.
3. Return expressions agree with the declared return type.
4. Schema records are checked for missing required fields and invalid field types.
5. Numeric conversions are explicit and predictable.
6. Diagnostics identify source locations and avoid cascading errors where possible.

## Compatibility

A type mapping to C++, C, Rust, Python, JavaScript, TypeScript, C#, Java, or Swift is a backend-specific mapping. The common type model remains authoritative; unsupported or lossy mappings must produce a diagnostic instead of silently generating misleading code.

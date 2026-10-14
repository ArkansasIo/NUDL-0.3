# NUDL 0.3 Proposed Language Specification

**Status:** Draft proposal for the 0.3 development line. This document is the design target, not a claim that every rule is implemented in the native C++ compiler or browser IDE.

## 1. Purpose and scope

NUDL (Noodle Unified Data Language) is intended to represent typed values, functions, records, schemas, datasets, validation, and transformations in a readable text format. JSON, CSV, SQL, spreadsheet formats, CSS, and other programming languages are interoperability targets or design influences; they are not embedded syntaxes.

## 2. Source files and lexical rules

- Source files use UTF-8 text.
- Identifiers begin with an ASCII letter or underscore and continue with letters, digits, or underscores in the initial profile.
- Whitespace separates tokens; newlines do not terminate a statement by themselves.
- `# line comment` and `// line comment` are proposed line-comment forms.
- Strings use double quotes and support documented escapes such as `\\n`, `\\r`, `\\t`, `\\\\`, and `\\"`.
- Integer and decimal literals are supported in the initial profile. Exponent notation, numeric separators, and exact overflow rules need conformance tests before being considered stable.
- Operators and punctuation are defined in `grammar/NUDL-0.3.ebnf`.

The native lexer and IDE lexer are separate implementations; differences must be reported and resolved through shared fixtures.

## 3. Values and types

The proposed primitive types are `bool`, signed and unsigned fixed-width integers (`i8/i16/i32/i64`, `u8/u16/u32/u64`), floating point (`f32/f64`), `text`/`string`, `bytes`, `null`, and `void`.

Composite types include arrays (`T[]`), named records, and schema-constrained records. Map/dictionary and optional types are planned but require final syntax.

See [Type System](../docs/TYPE-SYSTEM.md) for the detailed type contract.

## 4. Declarations

### Bindings

```nudl
let count: i64 = 3
const title: text = "NUDL"
```

`let` denotes a reassignable binding and `const` a non-reassignable binding. Type inference may be used when the initializer gives an unambiguous type.

### Functions

```nudl
fn add(a: i64, b: i64) -> i64 {
    return a + b
}

fn main() {
    print(add(20, 22))
}
```

Functions have named parameters and an optional return annotation in the proposed grammar. The current native parser requires an explicit return arrow/type in its existing implementation; the browser parser may differ. Do not rely on syntax variations until conformance tests settle them.

### Schemas and data

```nudl
schema Person {
    id: u64 required
    name: text required
    active: bool = true
}

data people: Person {
    { id: 1, name: "Ada", active: true }
    { id: 2, name: "Grace" }
}
```

A schema declares field names, types, requiredness, and optional defaults. A data declaration associates records with a named schema. Implementations should report missing required fields, unknown fields, and incompatible values rather than silently dropping or coercing them. Schema/data syntax is part of the design, but is not supported by the current native parser subset.

## 5. Expressions and precedence

The proposed precedence order, highest to lowest, is:

1. Parentheses, calls, indexing, member access.
2. Unary `!` and unary `-`.
3. `*`, `/`, `%`.
4. `+`, `-`.
5. `<`, `<=`, `>`, `>=`.
6. `==`, `!=`.
7. `&&`.
8. `||`.

Binary operators are left-associative unless a later normative rule explicitly says otherwise. Logical operators should short-circuit. Operator precedence must be verified by shared fixtures.

## 6. Statements and control flow

The design includes bindings, expression statements, `return`, `if`/`else`, and `while`. Blocks use braces. Semicolons may be accepted as optional terminators in the current profile; line-break and semicolon insertion rules are not implicit and must be documented if added.

Assignment, `break`, `continue`, pattern matching, exceptions, and asynchronous operations require explicit specification before becoming stable.

## 7. Runtime model

- Evaluation order is left-to-right for function arguments and binary operands, except short-circuit logical operators.
- An undefined name is a runtime error unless static analysis reports it earlier.
- Division by zero must produce a deterministic error rather than silently returning infinity.
- The interpreter must have configurable resource limits to prevent unbounded loops or recursion.
- Runtime values should have deterministic display formatting.
- Imported data must not execute as source code.

The browser interpreter and native interpreter are distinct and need parity tests.

## 8. Modules and imports

`module`, `import`, and `export` are planned keywords only until module resolution, path rules, cycle behavior, visibility, and package semantics are specified and implemented. The current CLI does not provide a package manager.

## 9. Interoperability

JSON, CSV, SQL, XLSX/ODS, and other language backends are explicit adapters. They must document encoding, null handling, numeric precision, date/time handling, duplicate fields, and lossy conversions. Imported SQL is data and must never execute merely because it was imported.

## 10. Diagnostics

Diagnostics should include severity, stable code, message, and one-based source location; ranges and suggested fixes are encouraged. See [Diagnostics](../docs/DIAGNOSTICS.md).

## 11. Implementation status

The native C++23 repository contains a lexer, parser, AST, diagnostics, interpreter, CLI, and a C++ source emitter for a limited subset. Other target names are registered but not fully implemented. The browser IDE contains its own TypeScript lexer/parser/interpreter and several source emitters. Schema/data support, complete static typing, module resolution, comprehensive standard library, and cross-implementation conformance remain incomplete.

## 12. Compatibility and versioning

Language changes that alter parsing or runtime results require a spec/grammar update, regression fixtures, implementation changes, and release notes. Until the conformance suite passes, 0.3 behavior should be treated as a draft and implementation-specific differences documented.

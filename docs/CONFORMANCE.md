# NUDL 0.3 Conformance Plan

## Goal

The native C++ compiler and browser TypeScript implementation should share a versioned language contract and a common set of source fixtures. Each implementation must state which features are supported.

## Fixture layout

- `tests/fixtures/valid/`: programs expected to lex and parse.
- `tests/fixtures/invalid/`: malformed programs with expected diagnostic categories.
- `tests/fixtures/runtime/`: programs with expected output and return values.
- `tests/fixtures/codegen/`: programs and target-specific golden files.

## Test dimensions

1. Lexical rules and source locations.
2. Operator precedence and associativity.
3. Parser recovery and end-of-file handling.
4. Declaration and name resolution.
5. Type and schema validation.
6. Function calls, return values, and recursion limits.
7. Runtime values, equality, truthiness, and numeric errors.
8. Deterministic output from code generators.
9. Import/export round trips and malformed input.
10. CLI exit codes and paths containing spaces.

## Expected fixture metadata

A fixture may use a sibling JSON manifest with fields such as `kind`, `expectedDiagnostics`, `expectedOutput`, and `targets`. The manifest format itself should be versioned before becoming a stable public interface.

## Current status

The repository includes C++ smoke, interpreter, and code-generation tests. The browser IDE has a baseline TypeScript regression suite. Passing these suites does not yet establish full NUDL 0.3 conformance; cross-implementation fixtures and backend compilation tests remain future work.

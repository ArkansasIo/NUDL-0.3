# NUDL 0.3 Interoperability

## Principle

NUDL is its own language. JSON, CSV, SQL, spreadsheet formats, and other programming languages are interoperability targets—not embedded native syntaxes.

## Data interchange goals

- JSON: import/export nested values, arrays, and records.
- CSV: import/export tabular records with explicit column mapping.
- SQL: generate or import schema/data descriptions only through an explicit adapter. Never execute imported SQL as a side effect of parsing.
- XLSX/ODS: spreadsheet import/export through a separately versioned adapter.
- Language backends: emit source code from the common AST/IR, with documented target limitations.

## Deterministic conversion

Every importer should document:
1. Character encoding and malformed-input behavior.
2. Null and missing-field semantics.
3. Numeric parsing, precision, and overflow behavior.
4. Date/time representation and timezone handling.
5. Duplicate column/key behavior.
6. Schema inference versus explicit schema selection.
7. Lossy conversions and round-trip limitations.

## Security boundaries

Treat all imported files as untrusted input. Enforce size and nesting limits, avoid evaluating expressions from data files, parameterize database operations, and never execute SQL merely because it was imported or displayed.

## Status

These are architecture requirements for planned adapters. They do not imply that JSON, CSV, SQL, or spreadsheet adapters are all implemented in the current native compiler.

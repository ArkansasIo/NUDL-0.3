# NUDL Diagnostics and Error Handling

## Format

Human-readable CLI diagnostics should use:

```text
path/to/file.nudl:12:7: error: expected expression after '='
```

Editor integrations should expose the same information structurally:

- `code`: stable identifier when available.
- `severity`: `error`, `warning`, or `info`.
- `message`: concise explanation.
- `line`, `column`: one-based source location.
- `endLine`, `endColumn`: optional highlighted range.
- `help`: optional corrective suggestion.

## Diagnostic categories

| Prefix | Category | Examples |
|---|---|---|
| L | Lexing | unexpected character, unterminated string/comment |
| P | Parsing | missing delimiter, invalid expression |
| T | Types | incompatible assignment or return type |
| N | Names | unknown variable, duplicate function |
| S | Schema/data | missing required field, unknown schema |
| G | Code generation | unsupported target construct |
| R | Runtime | division by zero, unknown function, step limit |
| I | I/O / CLI | unreadable input or unwritable output |

Codes in this table are category conventions, not a promise that every listed code is already emitted by the current implementation.

## Recovery rules

- A lexical error should preserve enough token position information to continue analysis where safe.
- A parser should synchronize at statement or declaration boundaries instead of looping forever.
- Semantic analysis should report independent issues in one pass where practical.
- Runtime errors must stop the current execution and return a useful diagnostic.
- Never suppress an error simply to make code generation appear successful.

## Editor presentation

The IDE should show file, line, column, severity, and message; clicking a diagnostic should move the caret to its source location. Diagnostics should be cleared or replaced when the source is re-analyzed, not accumulated indefinitely across unrelated edits.

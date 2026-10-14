# NUDL 0.3 Feature Status

This matrix is the conservative status record for the current repositories. “Implemented” means a code path exists; it does not imply complete spec conformance.

| Feature | Native C++ | Browser IDE | Notes |
|---|---|---|---|
| Lexer and token locations | Implemented subset | Implemented subset | Edge-case parity still needed |
| Function declarations | Implemented subset | Implemented subset | Native parser requires explicit return arrow/type |
| Typed parameters | Parsed | Parsed | Full static type checking not complete |
| Bindings | Implemented subset | Implemented | Const enforcement differs / incomplete |
| Arithmetic and comparison | Implemented subset | Implemented subset | Conformance tests required |
| Logical short-circuit operators | Not fully specified/implemented | Interpreter supports logical operators | Cross-runtime parity needed |
| If/else | Basic syntax | Basic syntax | Native else-if behavior not complete |
| While | Basic syntax | Basic syntax | Native assignment statements are missing |
| Arrays | AST/runtime subset | Implemented subset | Native C++ codegen currently rejects array literals |
| Struct declarations/instances | Not fully integrated | AST support present | Native parser does not parse declarations |
| Schema declarations | Not implemented in native parser | Parsed and analyzed | Runtime parity needed |
| Data declarations | Not implemented in native parser | Parsed and loaded | Schema validation is incomplete |
| Member/index expressions | Not implemented in native parser | AST/runtime support | Native AST needs extension |
| Static semantic/type analysis | Not implemented as a full pass | Baseline diagnostics | Expand scope/name/type checking |
| Interpreter | Basic runtime | Browser runtime | Separate implementations |
| C++ source generation | Implemented subset | Emitter present | Must compile emitted fixtures in CI |
| Other target generators | Native targets are registered, but backend is not implemented | Emitters present | Do not claim target verification without toolchain tests |
| JSON/CSV/SQL/XLSX adapters | Planned | Planned | Explicit conversion and security rules required |
| Module system/package manager | Planned | Planned | Keywords alone do not imply support |
| Shared conformance suite | Planned | Baseline tests exist | Highest-priority parity task |

## How to update this table

Update this table only after the feature has a source implementation and a regression test. For generated code, add a target-toolchain compile or execution test before marking a backend verified. Keep proposed syntax clearly separated from the runnable subset.

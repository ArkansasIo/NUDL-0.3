# NUDL 0.3 Roadmap

This roadmap separates present behavior from future goals. A feature is complete only when implementation, tests, documentation, and known limitations agree.

## Milestone A — reproducible foundation

- [x] CMake-based C++23 project layout.
- [x] Lexer, parser, AST, diagnostics, CLI driver.
- [x] Initial interpreter and C++ source emitter.
- [x] Smoke, interpreter, and code-generation test targets.
- [x] Language, CLI, type-system, security, interoperability, and conformance documentation.
- [ ] Build and run the complete test suite on Windows, Linux, and macOS in CI.

## Milestone B — language correctness

- [ ] Stable normative EBNF and token definitions.
- [ ] Source spans and stable diagnostic codes.
- [ ] Scope-aware name resolution and duplicate declaration checks.
- [ ] Static type checking and explicit conversion rules.
- [ ] Schema/data declarations in both native and browser parsers.
- [ ] Shared valid/invalid fixtures consumed by C++ and TypeScript.

## Milestone C — runtime

- [ ] Complete record/map values and schema validation.
- [ ] Function scopes, recursion limits, deterministic errors.
- [ ] Standard-library contract and unit tests.
- [ ] Dataset filtering/transformation syntax with explicit semantics.
- [ ] Resource limits for source, memory, and execution.

## Milestone D — code generation

- [ ] Correct string escaping and type mappings per target.
- [ ] Golden tests for each emitter.
- [ ] CI compilation/execution for each installed target toolchain.
- [ ] Explicit unsupported-feature diagnostics rather than silently incorrect output.
- [ ] WebAssembly validation and runtime integration.

## Milestone E — tooling and ecosystem

- [ ] CLI commands for check, run, emit, format, and version.
- [ ] JSON/CSV adapters with documented round-trip rules.
- [ ] Package manifest and lockfile design, followed by signed package verification.
- [ ] Language server protocol integration.
- [ ] IDE/native compiler conformance report.

## Release gate

Do not call NUDL 0.3 production-ready until the language contract is frozen, supported features are covered by automated tests, native and browser implementations agree on shared fixtures, and all advertised code-generation targets are honestly classified as verified or experimental.

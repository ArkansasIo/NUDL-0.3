# Changelog

## Unreleased — NUDL 0.3 development

### Native compiler
- Hardened parser token access at end-of-input and changed failed expectations to report diagnostics without advancing arbitrarily.
- Added simple variable assignment statements to the native AST, parser, interpreter, and C++ emitter.
- Improved C++ string-literal escaping for backslashes, quotes, and control characters.
- Added lexer decoding for carriage returns and escaped characters.
- Expanded native regression tests for string escaping, assignment, while loops, and else-branch output.
- Added cross-platform CMake/CTest GitHub Actions workflow.

### Documentation
- Expanded the proposed specification and EBNF grammar.
- Added CLI, type-system, standard-library, diagnostics, interoperability, security, conformance, feature-status, roadmap, and contribution guides.
- Updated examples and clarified the difference between proposed syntax and the currently implemented native subset.

### Known limitations
- Native schema/data declarations, full static type checking, modules/imports, and most non-C++ backends remain unimplemented.
- Native and browser implementations do not yet share a conformance fixture suite.
- Automated builds and tests must be checked in GitHub Actions; code changes alone do not prove that CI passes.

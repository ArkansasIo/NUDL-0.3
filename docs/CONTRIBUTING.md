# Contributing to NUDL 0.3

## Before changing the language

1. Check `spec/SPEC-0.3.md` and `grammar/NUDL-0.3.ebnf`.
2. State whether the change affects syntax, runtime semantics, the CLI, a backend, or documentation.
3. Add or update examples and conformance tests.
4. Keep proposed features clearly labeled until implemented.

## Local checks

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Pull request checklist

- [ ] Source compiles under C++23.
- [ ] Existing tests pass.
- [ ] New behavior has a focused test.
- [ ] Diagnostics include useful locations.
- [ ] Documentation reflects actual behavior.
- [ ] Unsupported features fail explicitly.
- [ ] No secrets, generated build artifacts, or unrelated vendored files were added.

## Compatibility

Do not change language semantics silently. If a syntax or runtime behavior changes, update the spec, EBNF, examples, native implementation, browser implementation, and shared fixtures as appropriate.

# Native NUDL Test Suite

The native test targets are declared in the root CMakeLists.txt.

## Run all tests

```sh
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build --build-config Release --output-on-failure
```

## Current tests

- cpp/smoke_test.cpp: parser smoke test and string escape decoding.
- cpp/interpreter_test.cpp: initial interpreter/function-call regression.
- cpp/codegen_test.cpp: C++ emitter, escaped string literals, and else branch output.

These are small regression tests, not a complete conformance suite. Add one focused test for each new syntax rule, runtime behavior, diagnostic, or backend correction.

# NUDL 0.3 — Noodle Unified Data Language

NUDL is a proposed, human-readable programming and data language intended to combine typed values, functions, schemas, records, datasets, validation, and transformations in one coherent syntax. JSON, CSV, SQL, spreadsheets, CSS, and existing programming languages are interoperability influences—not embedded native syntaxes.

> **Status:** Active 0.3 development. The specification and repository are broader than the currently implemented native compiler subset. Consult the support notes before relying on a feature.

## Quick start

The intended native workflow is plain-text source `.nudl` → `nudlc` → generated source.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Example:

```sh
./build/nudlc examples/hello-world.nudl --target cpp --emit build/hello.cpp
```

On Windows, run the generated `nudlc.exe` from the build directory and adjust file paths as needed. See [CLI Reference](docs/CLI-REFERENCE.md) for the Notepad workflow and exit codes.

## Language example

```nudl
fn add(a: i64, b: i64) -> i64 {
    return a + b;
}

fn main() -> i64 {
    let answer: i64 = add(20, 22);
    print(answer);
    return 0;
}
```

Schema and dataset syntax is part of the design; not all schema/data declarations are supported by the native compiler yet:

```nudl
schema Person {
    id: u64 required
    name: text required
}

data people: Person {
    { id: 1, name: "Ada" }
    { id: 2, name: "Grace" }
}
```

## Repository map

- `03-compiler/`: C++23 lexer, parser, AST, CLI, interpreter, and code-generation source.
- `spec/`: proposed versioned language contract.
- `grammar/`: EBNF draft.
- `docs/`: architecture, language, CLI, type-system, standard-library, diagnostics, interoperability, security, conformance, contributor guide, and roadmap.
- `examples/`: sample `.nudl` programs and data declarations.
- `07-tests/`: C++ smoke, interpreter, and code-generation tests.
- `runtime/` and `stdlib/`: runtime and standard-library design material.

## Documentation index

- [Language overview](docs/LANGUAGE.md)
- [Proposed specification](spec/SPEC-0.3.md)
- [EBNF grammar](grammar/NUDL-0.3.ebnf)
- [Architecture](docs/ARCHITECTURE.md)
- [CLI reference](docs/CLI-REFERENCE.md)
- [Type system](docs/TYPE-SYSTEM.md)
- [Standard library](docs/STANDARD-LIBRARY.md)
- [Diagnostics](docs/DIAGNOSTICS.md)
- [Interoperability](docs/INTEROPERABILITY.md)
- [Security model](docs/SECURITY.md)
- [Conformance plan](docs/CONFORMANCE.md)
- [Roadmap](docs/ROADMAP.md)
- [Contributing](docs/CONTRIBUTING.md)
- [Feature status matrix](docs/FEATURE-STATUS.md)
- [Native test guide](07-tests/README.md)

## Current implementation notes

- The native implementation is C++23 and uses CMake.
- The native C++ source emitter is the implemented backend; other registered target names are not yet complete native backends.
- The native AST/compiler currently supports a subset centered on functions, bindings, expressions, control flow, and basic runtime evaluation.
- Schema/data syntax, static type checking, imports/modules, full data transformations, and complete backend parity remain work in progress.
- The browser implementation in [NUDL-IDE](https://github.com/ArkansasIo/NUDL-IDE) is a separate TypeScript implementation. Shared conformance fixtures are needed to guarantee equivalent behavior.

## Design principles

1. Human-readable source with explicit syntax.
2. Deterministic parsing and predictable runtime behavior.
3. Structured diagnostics with source locations.
4. Explicit conversion and interoperability boundaries.
5. A clear distinction between implemented features, proposals, and experimental backends.
6. Tests and documentation evolve with language semantics.

## Contributing

See [docs/CONTRIBUTING.md](docs/CONTRIBUTING.md). New language features should update the spec, grammar, native implementation, IDE implementation, examples, and conformance fixtures as applicable.

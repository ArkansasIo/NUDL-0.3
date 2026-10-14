# NUDL 0.3 Language Overview

NUDL (Noodle Unified Data Language) is an evolving language for typed program logic and structured data. The goal is to make functions, schemas, records, datasets, and validation readable in plain-text files while keeping syntax deterministic for tools.

## First program

```nudl
fn main() -> i64 {
    print("Hello from NUDL 0.3")
    return 0
}
```

Save as UTF-8 text, such as `hello-world.nudl`. See [CLI Reference](CLI-REFERENCE.md) for building and invoking the native compiler.

## Variables and expressions

```nudl
let count: i64 = 40
const label: text = "answer"
let answer = count + 2
print(label, answer)
```

The native parser currently requires an explicit return arrow and type for every function, including `main`; use `-> i64` and return a status code for examples intended to run with `nudlc`. The proposed semantics distinguish reassignable `let` bindings from non-reassignable `const` bindings. Type inference and enforcement vary by implementation today.

## Functions

```nudl
fn add(a: i64, b: i64) -> i64 {
    return a + b
}

fn main() -> i64 {
    print(add(19, 23))
    return 0
}
```

Functions use typed parameters and can declare a return type. The exact optional-return-annotation rule remains a compatibility issue between the design grammar and current native parser.

## Branching and loops

```nudl
fn main() -> i64 {
    let n = 0
    while (n < 3) {
        print(n)
        n = n + 1
    }
    if (n == 3) {
        print("finished")
    } else {
        print("unexpected")
    }
    return 0
}
```

The native parser and interpreter now support simple name assignments such as `n = n + 1`. Nested lexical scopes, const reassignment protection, and full static type checking are not yet complete.

## Schemas and datasets

```nudl
schema User {
    id: u64 required
    name: text required
    enabled: bool = true
}

data users: User {
    { id: 1, name: "Ada" }
    { id: 2, name: "Grace", enabled: false }
}
```

This demonstrates the intended data-oriented syntax. Schema/data parsing and runtime validation are design goals and are not currently supported by the native parser.

## Arrays and standard library

The design includes array values and utility functions such as `print`, `len`, `str`, `typeof`, math helpers, and regex helpers. The browser interpreter currently implements some of these built-ins. The native runtime and generated targets do not yet share a complete standard library.

## Compiler and IDE

- [Native compiler](https://github.com/ArkansasIo/NUDL-0.3): C++23/CMake CLI, parser, interpreter, and staged source generation.
- [Browser IDE](https://github.com/ArkansasIo/NUDL-IDE): TypeScript editor, diagnostics, interpreter, visual Blueprint editor, workspace tools, and code emitters.

These are separate implementations. Check [Conformance Plan](CONFORMANCE.md) and the IDE [Language Support Matrix](https://github.com/ArkansasIo/NUDL-IDE/blob/main/docs/LANGUAGE-SUPPORT-MATRIX.md) for implementation status.

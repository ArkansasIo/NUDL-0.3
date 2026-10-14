# NUDL 0.3 CLI Reference

## Purpose

The native command-line driver is `nudlc`. It reads UTF-8 source from a plain-text `.nudl` file, tokenizes and parses it, reports diagnostics, and emits generated source. It is designed for a workflow that begins in Notepad or another text editor.

## Build

From the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build --output-on-failure
```

C++23 and CMake 3.20 or newer are required by the project configuration. A C++ compiler such as MSVC, Clang, or GCC must be installed.

## Usage

```text
nudlc <file.nudl> [--target <language>] [--emit <output-file>]
```

Examples:

```sh
nudlc examples/hello.nudl
nudlc examples/hello.nudl --target cpp --emit build/hello.cpp
nudlc examples/hello.nudl --target python --emit build/hello.py
```

The native compiler currently implements a deliberately limited language subset. The CLI accepts target names for future backends, but the existence of a target name does not mean that target is implemented. At this revision, C++ is the implemented native code-generation backend; unsupported targets return a clear error.

## Exit status

- `0`: source accepted and output produced.
- `1`: lexical, syntax, or code-generation error.
- `2`: usage, unknown option, input-file, or output-file error.

Diagnostics use `file:line:column: error: message` where source location is available.

## Windows / Notepad workflow

1. Save source as UTF-8 plain text, for example `hello.nudl`.
2. Open PowerShell in the repository build folder.
3. Run `./nudlc.exe ..\examples\hello.nudl --target cpp --emit hello.cpp` (adjust paths to the file you saved).
4. Compile the emitted C++ with your installed compiler.
5. Run the resulting executable.

The compiler does not silently execute arbitrary shell commands or invoke external compilers on your behalf. Code generation and native compilation are separate steps.

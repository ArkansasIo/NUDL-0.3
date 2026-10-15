# NUDL Extension Packages

**Status: proposal for NUDL 0.3; not implemented by the native compiler yet.**

This proposal defines how NUDL tooling may discover, validate, distribute, and eventually load extensions. It deliberately separates a normal .nudl source program from an installable extension package.

## Terminology

- **Source file**: UTF-8 NUDL source, conventionally ending in .nudl.
- **Extension manifest**: JSON metadata describing an extension's identity, version, entry source, permissions, and declared capabilities.
- **Extension package**: a ZIP-based archive with the suffix .nudlext (recommended) to avoid confusing a package archive with a plain .nudl source file.
- **Extension runtime**: a future, capability-limited host that can validate manifests and expose explicitly registered APIs.

The earlier idea of using .nudl for both source text and a ZIP archive is ambiguous. NUDL 0.3 should retain .nudl for source files and use .nudlext for an archive package. A package may contain extension.nudl as its entry source.

## Package layout

    my-extension.nudlext
    ├── manifest.json
    ├── extension.nudl
    ├── README.md
    ├── schemas/
    └── templates/

## Manifest example

    {
      "format": "org.nudl.extension",
      "formatVersion": 1,
      "name": "app-framework-sdk",
      "version": "0.1.0",
      "description": "Application framework template extension",
      "runtime": "nudl-extension-v1",
      "entry": "extension.nudl",
      "permissions": ["template.read", "project.generate"],
      "capabilities": ["application-template", "api-template", "gui-template"]
    }

## Security requirements

1. Validate manifest shape and semantic version before loading source.
2. Reject absolute paths, parent-directory traversal, duplicate archive paths, symlinks, oversized files, and suspicious compression ratios.
3. Keep all extraction paths within a dedicated staging directory.
4. Never execute shell commands from extension metadata.
5. Treat declared permissions as requests, not automatic grants.
6. Require host-side allowlisting for filesystem, network, process, and code-generation operations.
7. Default to dry-run and no-overwrite behavior for generated files.
8. Keep package loading separate from compilation and execution.
9. Add package signing and publisher trust as a later versioned feature.

## Runtime lifecycle (planned)

    discover -> inspect manifest -> validate package -> request permissions
             -> parse entry source -> check capabilities -> register extension
             -> invoke approved command -> report result

A manifest does not grant authority by itself. The host must approve each capability and provide a constrained API surface.

## Current implementation status

The repository currently contains a C++23 lexer/parser/interpreter/code generator for a subset of the NUDL language. The native parser does not currently implement extension declarations, package loading, permissions, or an extension registry. The example under examples/extensions/ is therefore a design fixture, not a compilable program. Do not represent it as executable until parser/runtime support and conformance tests are added.

## Planned CLI

    nudlc extension inspect my-extension.nudlext
    nudlc extension validate my-extension.nudlext
    nudlc extension list my-extension.nudlext
    nudlc extension pack ./my-extension --output my-extension.nudlext

These commands are proposals and are not implemented in the current CLI.

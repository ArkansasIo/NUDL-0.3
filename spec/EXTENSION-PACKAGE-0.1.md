# NUDL Extension Package Specification 0.1

**Status:** Draft proposal for NUDL 0.3.

## 1. Goals

Provide a versioned, portable package format for distributing declarative NUDL extensions without conflating archive containers and source files.

## 2. File naming

- .nudl: UTF-8 source program.
- .nudlext: ZIP-based extension package.
- manifest.json: required package metadata inside the archive.
- extension.nudl: default entry source.

## 3. Required manifest fields

| Field | Type | Requirement |
|---|---|---|
| format | string | Must be org.nudl.extension |
| formatVersion | integer | Initially 1 |
| name | string | 2–80 chars; letters, digits, dot, underscore, hyphen |
| version | string | Semantic version |
| runtime | string | nudl-extension-v1 |
| entry | string | Relative path to entry source |
| permissions | string array | Capability requests |
| capabilities | string array | Declared features |

## 4. Package constraints

Initial recommended limits:
- compressed package: 10 MiB
- total uncompressed content: 25 MiB
- individual file: 5 MiB
- maximum archive entries: 256
- maximum compression ratio: 100:1

Implementations may use stricter limits. Limits must be documented and checked before extraction.

## 5. Permission model

Permissions are named capability requests such as template.read, project.generate, filesystem.read, or network.request. A runtime must not grant permissions simply because the manifest lists them. The user or administrator and host policy decide which capabilities are available.

## 6. Error behavior

Package operations should produce stable diagnostic codes:
- NEX001: invalid archive
- NEX002: missing manifest or entry
- NEX003: unsupported package version
- NEX004: invalid manifest
- NEX005: unsafe archive path
- NEX006: resource limit exceeded
- NEX007: permission denied
- NEX008: unsupported runtime
- NEX009: source parse failure

Diagnostics should include the relevant path when safe and available, but never include secret data.

## 7. Compatibility

Package format versions and language versions are independent. A package manifest should declare both its package format and runtime target. Unknown major format versions must be rejected, not guessed.

## 8. Implementation state

This document specifies behavior; it does not claim the current C++ compiler implements it. Parser support, archive handling, permission enforcement, CLI integration, and conformance tests remain future implementation work.

# Extension Package Conformance Cases

**Status:** Test plan; these cases are not yet wired into the C++ test runner.

## Manifest
- Accept valid format version 1 manifest.
- Reject missing required fields.
- Reject invalid semantic version.
- Reject unsupported runtime identifier.
- Reject duplicate or malformed permission entries.

## Archive safety
- Reject absolute paths and parent-directory traversal segments.
- Reject duplicate archive entry names.
- Reject symlinks.
- Reject excessive archive entry count, file size, total size, and compression ratio.
- Reject missing manifest.json or entry source.
- Ensure extraction cannot escape the staging root.
- Ensure existing files are not overwritten by default.

## Permission behavior
- A declared permission does not automatically grant access.
- A denied permission prevents the operation and returns NEX007.
- Unknown capabilities are rejected or ignored only according to an explicit compatibility policy.

## Source integration
- Validate entry source using the selected NUDL language version.
- Report source diagnostics with package path and line/column.
- Do not execute extension code during inspection or validation.

## CLI
- Inspect reports name, version, runtime, entry, and capabilities.
- Validate exits nonzero for invalid packages.
- Pack output is deterministic where archive metadata permits.
- All failures produce stable exit codes and a concise diagnostic.

# Noodle Build and Versioning

## Version

Noodle uses MAJOR.MINOR.PATCH project versions. Development releases may append -dev.

## Build number

A build number identifies a particular generated build within a development or release stream.

Example:
Version: 0.3.0-dev
Build number: 42
Build ID: NUDL-0.3-DEV-0042

## Build ID

Format:
NUDL-{language-version}-{channel}-{build-number}

Examples:
- NUDL-0.3-DEV-0001
- NUDL-0.3-CI-0042
- NUDL-0.3-RC-0100
- NUDL-1.0-RELEASE-0001

## Build name

Build names are descriptive human-readable artifact labels.

## Credits

Build credits must represent actual contributors, not hypothetical team members.

## Release identity

Every release artifact should contain product, version, build number, build ID, Git revision, target, architecture, toolchain, dependencies, and reproducibility metadata.

The language version and compiler version remain separate compatibility identifiers.

# AGENTS.md

## Project Summary
- CLI tool written in C.
- Build uses Zig build system.
- Tests are TDD-first and use cmocka.

## Build & Test
- Configure/build: `zig build`
- Run tests: `zig build test`
- Notes: cmocka is included via git submodule in `external/cmocka`.

## Layout
- `src/` production code
- `tests/` cmocka tests
- `external/` third-party deps (cmocka submodule)

## Conventions
- Prefer small, focused functions.
- Keep modules separated by responsibility.
- Write/extend tests before implementation changes.
- Use minimal C standard library features; avoid platform-specific APIs unless required.

## Dependencies
- C toolchain provided by Zig.
- cmocka submodule pinned to a tag/commit.

## Workflow
- Add a failing test first.
- Implement minimal change to pass.
- Refactor with tests green.

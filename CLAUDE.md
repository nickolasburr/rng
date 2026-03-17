# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

`rng` is a lightweight C command-line utility that streams line ranges from files or stdin to stdout. It combines the behavior of `sed -n '<START>,<END>p'` and `tail -n`, supporting multiple ranges via the `:` operator (e.g., `rng 5,10:17,22 main.c`).

## Build Commands

```sh
make          # Build the rng binary
make clean    # Remove binary and debug symbols
make install  # Install binary to $(PREFIX)/bin and man page (default PREFIX=/usr/local)
make uninstall
```

Compiler: GCC with `-I$(INCLUDE) -pthread -lz` flags. No autoconf/cmake — just `make`.

There is no test suite. Validation is done manually by running the binary.

## Architecture

The project is a single-binary C program with headers in `include/` and sources in `src/`.

**Core modules:**
- `main.c` — Entry point: parses args, tokenizes range strings, opens files, runs the line-filtering loop
- `argv.c/h` — Usage/help output
- `range.h` — `Range_T` struct (`unsigned int start, end`)
- `mem.c/h` — Memory wrappers (`ALLOC`, `FREE`, `CALLOC`, `RESIZE`) with error handling
- `except.c/h` — Exception framework using `setjmp`/`longjmp` with `TRY`/`EXCEPT`/`FINALLY`/`END_TRY` macros
- `assert.c/h` — Custom assert that raises exceptions
- `utils.c/h` — String utilities and POSIX `stat`-based filesystem helpers
- `error.c/h` — Simple error code comparison utility
- `common.h` — Global macros: `PROGNAME`, `RNG_VERSION`, `is_null`

**Range parsing and filtering logic (all in `main.c`):**
1. Range string (e.g., `"5,10:17,22"`) is split by `:` into individual ranges
2. Each range is split by `,` into start/end values
3. Per-line loop checks if current line number falls within any `Range_T` — if so, writes to stdout
4. An end value of `0` means open-ended (no upper bound)

**Platform handling:** `common.h` includes `<limits.h>` on Apple and `<linux/limits.h>` elsewhere.

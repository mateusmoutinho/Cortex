# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Cortex is a C web application sandbox/template designed for LLM-driven development ("vibecoding"). It provides a sandboxed API in `app.c` so developers can build web apps in C without touching low-level HTTP or memory management internals.

## Build & Run Commands

**Simple compile and run (most common):**
```bash
gcc main.c -o app
./app
```

**Debug mode with hot-reload** (requires Darwin + CWebStudioFirmware):
```bash
darwin run_blueprint --target debug --compiler "gcc"
```

**Other build targets** (require Darwin, most require Docker/Podman):
```bash
darwin run_blueprint --target amalgamation          # Single-file release/Cortex.c
darwin run_blueprint --target static_linux --provider docker
darwin run_blueprint --target windows --provider docker
darwin run_blueprint --target deb --provider docker
darwin run_blueprint --target rpm --provider docker
```

Default server port is 3000, configurable via `--port` flag.

## Architecture

**Two-file model:**
- `main.c` — Server infrastructure, HTTP routing, and the `appdeps` function pointer table wiring. This bridges CWebStudio (HTTP server library) to the sandbox API. Not intended for direct editing by application developers.
- `app.c` — Application code sandbox. All application logic goes here. Uses no `#include` directives; instead accesses all functionality through the `appdeps` struct passed as a function pointer table.

**Key types in `app.c`:**
- `appdeps` — Struct of function pointers providing: stdio, memory allocation, HTTP request/response, JSON (cJSON-based), file I/O, CLI argument parsing, and HTTP client
- `appstart` — Returned by `public_appstart()` to configure port, server handler, and custom props
- `public_appstart(appdeps *deps)` — Entry point called at startup; configure and return `appstart`
- The server handler function (e.g. `private_mainserver`) receives `appdeps *deps` and `void *props`

**Dependencies** (header-only C libraries in `dependencies/`):
- **CWebStudio** (v5.3.0) — HTTP server
- **doTheWorld** (v11.2.0) — File I/O utilities
- **CArgvParse** (v0.0.2) — CLI argument parsing
- **BearHttpsClient** (v0.9.2) — HTTPS client

**Build system:** Darwin (Lua-based), configured in `darwinconf.lua` with build recipes in `builds/`.

## Key Constraints

- `app.c` must never use `#include` — all functionality comes through the `appdeps` function pointer table
- When modifying `app.c`, always return the full file content including the type definitions and comments at the top
- `main.c` wires the `appdeps` struct to actual library implementations; changes here affect the entire sandbox API surface

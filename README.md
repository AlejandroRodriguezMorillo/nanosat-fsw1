# nanosat-fsw

[![CI](https://github.com/AlejandroRodriguezMorillo/nanosat-fsw1/actions/workflows/ci.yml/badge.svg)](https://github.com/AlejandroRodriguezMorillo/nanosat-fsw1/actions/workflows/ci.yml)

Flight software skeleton for a CubeSat, written from scratch in C99 as a learning project. It implements the core of a satellite's on-board software: a mode state machine, error detection, and a CCSDS-style telemetry frame.

Built while preparing to join **FyCUS**, the nanosatellite group at the University of Seville.

## What it does

- **Mission state machine** — `BOOT → DETECTION → NOMINAL`, with `SAFE` as the protective fallback. Errors in nominal mode force a transition to safe mode; recovery always re-runs hardware checks before returning to operations.
- **CRC-16/CCITT** — error detection for telemetry, verified against the standard reference vector (`"123456789"` → `0x29B1`).
- **CCSDS-style telemetry frame** — 14-byte frame with the real CCSDS Attached Sync Marker (`0x1ACFFC1D`), big-endian fields, and a CRC protecting the whole frame.
- **Frame verifier** — recomputes the CRC and rejects corrupted frames.

## Architecture

```
src/
├── core/          portable flight logic (no OS or hardware dependencies)
│   ├── fsm.c/h    mission state machine
│   ├── crc16.c/h  CRC-16/CCITT
│   └── tlm.c/h    telemetry frame builder / verifier
└── app/
    └── main.c     demonstration driver
```

`core/` is written to compile unchanged on a PC and on an embedded target; only the application layer (sensor drivers, radio) changes.

## Telemetry frame layout

| Offset | Size | Field |
|---|---|---|
| 0 | 4 | Sync marker `1A CF FC 1D` (CCSDS ASM) |
| 4 | 1 | Frame version |
| 5 | 1 | FSM state |
| 6 | 2 | Timestamp (ticks, big-endian) |
| 8 | 2 | Temperature, 0.1 °C signed (big-endian) |
| 10 | 2 | Battery voltage, mV (big-endian) |
| 12 | 2 | CRC-16 over bytes 0–11 (big-endian) |

## Build and run

Requires CMake ≥ 3.16 and a C99 compiler.

```bash
cmake -S . -B build
cmake --build build
./build/nanosat
```

The build uses `-Wall -Wextra -Wpedantic -Werror`: the code compiles with zero warnings.

## Example output

```
[BOOT]
event: BOOT_DONE -> [DETECTION]
event: CHECKS_PASSED -> [NOMINAL]
event: ERROR -> [SAFE]
event: RECOVERED -> [DETECTION]
CRC16("123456789") = 0x29B1 (esperado: 0x29B1)
frame (14 bytes): 1A CF FC 1D 01 02 00 2A 00 FD 0E D8 98 F2
verify: OK
verify tras corromper: BAD
```

## Roadmap

- [x] Mission state machine with safe mode
- [x] CRC-16/CCITT with reference vector check
- [x] CCSDS-style telemetry frame and verifier
- [ ] Cooperative task scheduler (periodic telemetry, health checks)
- [ ] Software-in-the-loop simulator with fault injection
- [ ] Unit tests and GitHub Actions CI
- [ ] Ground station decoder (Python)

## Design notes

- C99, no dynamic allocation, no hardware or OS dependencies in `core/`.
- Explicit error codes and defensive bounds checks on every buffer.
- Every module has a header that documents its contract.
- The frame is serialized byte by byte (no `memcpy` of structs) to stay portable across architectures.

## License

MIT

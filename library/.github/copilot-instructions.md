## Quick context for code-writing agents

This repository is an embedded C++ (C++17) library for ATmega328P devices plus a Linux-hosted unit test suite.
Focus: hardware drivers (ADC, EEPROM, GPIO, Serial, TempSensor, Timer, Watchdog), small containers, simple ML (linear regression), and test harnesses.

Key layout
- `include/` — public headers organized by subsystem (e.g. `include/driver/tempsensor/interface.h`).
- `source/`  — implementation files mirroring `include/` paths (e.g. `source/driver/tempsensor/*.cpp`).
- `test/`    — unit & component tests (Google Test) + `makefile` to build tests on Linux.
- `libatmegacpp.cppproj` — Visual Studio / Microchip Studio project used to build the library on Windows.

Important patterns & conventions (use these exactly)
- Namespaces: drivers live under `driver::<component>` (e.g. `driver::tempsensor`). ML code uses `ml::...`.
- Interfaces: Each driver exposes an `Interface` in `include/driver/<component>/interface.h` and concrete implementations live under `source/driver/<component>/` and/or `include/driver/<component>/*.h` (stubs are under `stub.h`).
- Fixed-width types: use `<cstdint>`/`stdint.h` types (e.g. `int16_t`, `uint8_t`).
- noexcept: public APIs and most small functions are declared `noexcept`.
- Hardware abstraction: `include/arch/avr/hw_platform.h` includes real AVR headers, but when building tests the `TESTSUITE` macro switches to `include/arch/test/hw_platform.h`. Respect this conditional.

Test harness specifics (how tests work)
- Tests are compiled and run on Linux. See `test/README.md` for installing Google Test.
- Build & run tests from the `test/` directory:
  - `make` — build and run tests
  - `make build` — compile only
  - `make run` — run tests only
  - `make clean` — remove build artefacts
- To add source or test files, update `TEST_FILES` and `SOURCE_FILES` in `test/makefile` (the makefile explicitly lists test sources and the source files included into the test executable).

Testing conventions to follow when coding
- Use the `TESTSUITE` compile-time switch for test-only behavior. Example: `include/arch/avr/hw_platform.h` uses `#ifndef TESTSUITE` to include `<avr/io.h>`; otherwise it includes `arch/test/hw_platform.h` which maps registers to `test::Memory::data` and redefines `ISR`, `_delay_ms`, etc.
- The test platform provides register arrays and helper functions in `include/arch/test/hw_platform.h` and `source/arch/test/hw_platform.cpp` — prefer those abstractions rather than introducing new global state for tests.
- Stubs: driver stubs follow the pattern `include/driver/<name>/stub.h` and are used by tests (e.g. `driver/adc/stub.h`). Follow existing stub naming and minimal behavior.

Where to look for examples
- Temperature sensor interface: `include/driver/tempsensor/interface.h` (contract for sensors).
- Temp sensor TODO/shape: `include/driver/tempsensor/smart.h` (contains requirements/comments that implementations must satisfy).
- Test platform mapping & macros: `include/arch/test/hw_platform.h` and `source/arch/test/hw_platform.cpp` (shows how hardware registers, ISR, and delays are mocked).
- Test makefile & instructions: `test/makefile` and `test/README.md` (how tests are compiled/run and where to add files).
- Project file for Windows: `libatmegacpp.cppproj` (if you add headers/sources that must compile under Microchip Studio, they need to be referenced here).

Small coding contract for new drivers/impls
- Inputs: stick to fixed-width integer types, accept dependencies by reference (e.g. `adc::Interface&`), don't allocate global state.
- Outputs: return small numeric types (`int16_t`) or bool for initialization checks.
- Error modes: prefer returning sentinel values (existing code returns 0 for uninitialized temp sensor) and keep functions `noexcept` where existing APIs do.

Common pitfalls
- The library is built on Windows (Microchip Studio); tests run on Linux — don't assume host toolchain parity. Keep platform-specific code under the `arch/` switch.
- When adding files to tests, forgetting to update `test/makefile` (`TEST_FILES`/`SOURCE_FILES`) is a frequent source of “file not built” issues.
- The test platform maps many AVR macros to `test::Memory::data`. Do not attempt to include real AVR headers when compiling tests — rely on the `TESTSUITE` path.

If you change public headers
- Update `libatmegacpp.cppproj` (Windows project) if the header needs to be listed there for Microchip Studio builds.

What I (the agent) will do when editing code here
- Preserve namespace, header/source mirroring, and `noexcept`/fixed-type styles.
- Use `TESTSUITE`-aware approaches for behavior that needs to be testable on Linux.

Questions for maintainers / next steps
- Should I add a CI job to run the `test/` makefile on Linux (recommended)?
- Prefer explicit guidance on how to populate `libatmegacpp.cppproj` when new files are added (I can add a small helper script if desired).

Please review and tell me any missing patterns or desired automation to include.

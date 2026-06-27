# Aether

> A modular device driver framework for Apple Silicon.

Aether is a C++20 framework for building and testing user-space device drivers on Apple Silicon. It implements core systems including MMIO, interrupts, DMA, scheduling, memory management, and Metal-backed GPU compute within a unified runtime.

---

## Features

- Driver framework
- Hardware Abstraction Layer (HAL)
- Memory-Mapped I/O (MMIO)
- Interrupt controller
- DMA engine
- Thread scheduler
- Memory manager
- Metal-backed GPU device
- Virtual storage device
- Timer device
- Debug CLI
- Logging and tracing
- Fault injection
- Unit and integration tests

---

## Architecture

```text
CLI
 │
Driver Framework
 │
Device Manager
 │
├── MMIO
├── Interrupt Controller
├── DMA Engine
├── Scheduler
├── Memory Manager
 │
├── GPU Device (Metal)
├── Storage Device
└── Timer Device
 │
Apple Silicon (macOS)
```

---

## Repository Structure

```text
aether/
├── docs/
├── include/
├── src/
│   ├── core/
│   ├── driver/
│   ├── device/
│   ├── mmio/
│   ├── irq/
│   ├── dma/
│   ├── memory/
│   ├── scheduler/
│   ├── gpu/
│   ├── storage/
│   ├── timer/
│   ├── debug/
│   └── cli/
├── tests/
├── examples/
└── tools/
```

---

## Building

### Requirements

- Apple Silicon Mac
- macOS
- C++20
- CMake
- Xcode Command Line Tools

### Configure

```bash
cmake -B build
```

### Build

```bash
cmake --build build
```

### Run

```bash
./build/aether
```

---

## Roadmap

- [ ] Driver framework
- [ ] MMIO
- [ ] Interrupt controller
- [ ] DMA engine
- [ ] Memory manager
- [ ] Thread scheduler
- [ ] Metal GPU device
- [ ] Storage device
- [ ] Timer device
- [ ] Debug CLI
- [ ] Logging
- [ ] Tracing
- [ ] Fault injection
- [ ] Test suite
- [ ] Documentation

---

## License

This project is licensed under the GNU License.

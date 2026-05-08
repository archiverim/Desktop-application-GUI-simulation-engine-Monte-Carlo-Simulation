# Lotto 6/49 Simulator
A desktop GUI application built with C++ and SFML that simulates Lotto 6/49 outcomes using Monte Carlo methods.
## Features
- Interactive 7×7 grid to select 6 numbers
- Monte Carlo simulation (10,000 runs) to estimate match probabilities
- Expected value calculation per ticket
- Reset to run multiple simulations
## Files
| File | Description |
|---|---|
| `sim.cpp` | Console-based simulation with probability and expected value output |
| `gui.cpp` | SFML desktop GUI with interactive number grid |
| `lotto.h` | Shared core functions (combination, generateDraw, countMatches) |
| `tests.cpp` | Unit tests for core functions |
## Requirements
- C++ compiler (g++ via MSYS2 UCRT64)
- SFML: `pacman -S mingw-w64-ucrt-x86_64-sfml`
## Build & Run
**Console simulation:**
```bash
g++ sim.cpp -o sim
./sim.exe

Desktop GUI:

g++ gui.cpp -o gui -lsfml-graphics -lsfml-window -lsfml-system
./gui.exe

Unit tests:

g++ tests.cpp -o tests
./tests.exe

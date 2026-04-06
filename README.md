# cmake-init

[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)

A CMake C++ project generator that sets up a complete project with sensible defaults.

## Features

- Interactive prompts for project configuration
- C++ and C standard selection (C++11 through C++26, C11, C17, C23)
- Testing framework support (GTest, Catch2, Boost.Test)
- Static analysis integration (Clang-Tidy, Cppcheck)
- Modular project structure with separate `src/`, `include/`, and `tests/` directories
- FetchContent-based dependency management template
- Out-of-source builds enforced

## Requirements

- CMake 3.25 or higher
- C++23 compatible compiler (GCC 13+, Clang 17+, MSVC 2022+)

## Quick Start

```bash
cmake-init
```

This will prompt you through project configuration and output a complete CMake-based project structure.

## Usage

### Interactive Mode

Run `cmake-init` without arguments to start the interactive prompt:

```bash
./cmake-init
Project Location [.]: my_project
Project Name [my_project]: 
Project Version [0.1.0]: 
Target Type
  1. Executable
  2. Static Library
  3. Shared Library
Enter choice [1-3, default: 1]: 
...
```

### Generated Project Structure

```
project/
├── CMakeLists.txt
├── src/
│   ├── CMakeLists.txt
│   └── main.cpp
├── include/
│   ├── CMakeLists.txt
│   └── project/
│       └── header.h
└── tests/
    ├── CMakeLists.txt
    └── test_main.cpp
```

### Configuration

The tool is configured via `config.json`. Edit this file to customize:

- Prompts and default values
- Available options for choice questions
- Enabled/disabled features

## Building

```bash
cmake -B build
cmake --build build
```

### Build Options

| Option | Description | Default |
|--------|-------------|---------|
| `ENABLE_TESTS` | Build test suite | ON |
| `ENABLE_CLANG_TIDY` | Enable Clang-Tidy checks | OFF |
| `ENABLE_CPPCHECK` | Enable Cppcheck static analysis | OFF |

Example with options:

```bash
cmake -B build -DENABLE_CLANG_TIDY=ON
cmake --build build
```

## Testing

```bash
ctest --test-dir build
```

Run specific test suites:

```bash
ctest --test-dir build -R config
ctest --test-dir build -R formatter
```

## License

cmake-init is released under the GNU General Public License v2.0 or later (GPL-2.0+).

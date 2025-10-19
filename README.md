# ccut - C++23 Cut Command Implementation

A modern C++23 implementation of the Unix `cut` command-line tool with library architecture, comprehensive testing, and cross-platform support.

## Features

- **Field extraction** with customizable delimiters
- **Multiple field selection** (comma or space separated)
- **Standard input support** (pipeline-friendly)
- **C++23 features**: `std::expected`, `std::string_view`, `std::ranges`
- **Exception-free design** with proper error handling
- **Cross-platform**: Linux (GCC/Clang) and Windows (MSVC)
- **Comprehensive testing** with GTest

## Quick Start

### Build

```bash
# Debug build
mkdir build-debug && cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)

# Release build  
mkdir build-release && cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

### Usage

```bash
# Basic field extraction (tab-delimited)
./ccut -f2 sample.tsv

# Custom delimiter
./ccut -f1 -d, data.csv

# Multiple fields
./ccut -f1,2,3 sample.tsv
./ccut -d, -f"1 2" data.csv

# Standard input
echo "a,b,c" | ./ccut -d, -f1,3
```

## Examples

### Step 1: Basic Field Extraction
```bash
$ ./ccut -f2 tests/sample.tsv
f1
1
6
11
16
21
```

### Step 2: Custom Delimiter
```bash
$ ./ccut -f1 -d, tests/fourchords.csv | head -n3
Song title
"10000 Reasons (Bless the Lord)"
"20 Good Reasons"
```

### Step 3: Multiple Fields
```bash
$ ./ccut -f1,2 tests/sample.tsv
f0	f1
0	1
5	6
10	11
15	16
20	21
```

### Step 4: Standard Input
```bash
$ tail -n5 tests/fourchords.csv | ./ccut -d, -f"1 2"
"Young Volcanoes",Fall Out Boy
"You Found Me",The Fray
"You'll Think Of Me",Keith Urban
"You're Not Sorry",Taylor Swift
"Zombie",The Cranberries
```

## Architecture

- **Library**: `ccutlib` - Core field extraction and options parsing
- **Executable**: `ccut` - Command-line interface
- **Tests**: Comprehensive unit tests with GTest

## CI/CD

Automated testing on:
- **Ubuntu GCC 14** - Debug and Release builds
- **Ubuntu Clang 19** - Debug and Release builds  
- **Windows MSVC** - Debug and Release builds

## Requirements

- **C++23** compatible compiler
- **CMake 3.20+**
- **GTest** (for testing)

## License

This project is open source. See LICENSE file for details.

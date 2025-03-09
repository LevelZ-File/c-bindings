# levelz-c

> Header-only C Parser & API For LevelZ File Format

![GitHub Release](https://img.shields.io/github/v/release/LevelZ-File/c-bindings)

## Overview

Provides C bindings for the LevelZ file format. This library is header-only and does not require any additional dependencies.

## Installation

You can use the installers provided in the [releases](https://github.com/LevelZ-File/c-bindings/releases) section.

Alternatively, you can build the project from source.

Ensure you have [CMake](https://cmake.org/) installed on your system, then run the following commands:

```bash
# Clone Repo
git clone https://github.com/LevelZ-File/c-bindings
cd cpp-bindings

# Build Project, Install with CMake
cmake --build . --config Release --target install

## may require sudo
sudo cmake --build . --config Release --target install
```

## Usage

```c
#include <levelz.h>

int main() {
    Coordinate2D* coord = createCoordinate2D(0, 0);
    Coordinate3D* coord2 = createCoordinate3D(0, 0, 0);

    printf("Coordinate 2D: (%d, %d)\n", coord->x, coord->y);
    printf("Coordinate 3D: (%d, %d, %d)\n", coord2->x, coord2->y, coord2->z);
    return 0;
}
```

```c
#include <levelz.h>

int main() {
    Level2D* l = parseFile2D("path/to/file-2d.lvlz")
    Level3D* l2 = parseFile3D("path/to/file-3d.lvlz")
    return 0;
}
```

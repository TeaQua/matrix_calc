# Matrix Calculator

This project contains the matrix calculator from laboratory work 3. The
implementation includes the basic operations and the scalar addition from the
individual assignment.

## 1. Build and run the application

From this directory:

```text
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 2
./build/matrix_calculator
```

The code uses C++ exceptions for invalid dimensions, null input, invalid
matrices, and incompatible operation dimensions. Every returned `Matrix` owns
dynamic memory and must be released with `free_matrix`.

## 2. Unit tests and CTest

Tests are written with Google Test. CMake downloads Google Test with
`FetchContent` during the first configure, so the first configure requires
network access.

```text
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

The tests cover zero initialization, array conversion, addition,
multiplication, scalar addition, invalid dimensions, incompatible operations,
empty-matrix output, and safe release of an empty matrix. CTest is the standard
test runner used by the local build and by CI.

## 3. Doxygen documentation

Doxygen reads public API comments from `include/matrix.h` and writes HTML to
`docs/html`:

```text
doxygen Doxyfile
```

Open `docs/html/index.html` in a browser. Graphviz is enabled in `Doxyfile` so
call and class diagrams can be generated when the `dot` program is installed.

## 4. Valgrind

Valgrind checks the test executable for invalid memory access and leaks:

```text
valgrind --leak-check=full --show-leak-kinds=all \
  --errors-for-leak-kinds=definite,indirect --error-exitcode=1 \
  build/tests/matrix_tests
```

The non-zero exit code makes the check fail in CI when a memory error or a
definite/indirect leak is found.

## 5. Docker

The Dockerfile uses a builder stage to compile the application and a smaller
runtime stage to run only the resulting executable:

```text
docker build -t matrix-calculator .
docker run --rm matrix-calculator
```

Tests are disabled in the runtime image build because unit tests are already
run as a separate CI step.

## 6. CI/CD workflow

`.github/workflows/ci.yml` runs on pushes to `main` or `develop` and on pull
requests to `main`. It checks out the project, installs tools, configures and
builds CMake, runs CTest, checks memory with Valgrind, and generates Doxygen.
The generated HTML documentation is uploaded as a workflow artifact. Docker is
checked separately with the commands from the previous section, just as in the
laboratory instructions.

## Implemented API

- `create_matrix` creates a zero-initialized matrix.
- `free_matrix` releases the matrix memory.
- `matrix_add` adds two matrices of equal size.
- `matrix_multiply` calculates the standard matrix product.
- `matrix_add_scalar` adds a value to every element.
- `print_matrix` prints a formatted matrix.
- `matrix_from_array` copies row-major array data into a matrix.

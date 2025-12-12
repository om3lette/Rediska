# Rediska

## Building from source

### Prerequisites (vcpkg)

> [!NOTE]
> Add `--triplet x64-linux-release` to the vcpkg install to build dependencies in release.
> Replace `linux` with your OS if it is supported

```bash
git clone --branch 2025.10.17 --depth 1 https://github.com/microsoft/vcpkg.git && \
./vcpkg/bootstrap-vcpkg.sh && \
./vcpkg/vcpkg install
```

### CMake workflow

```bash
cmake --preset debug
cmake --build --preset debug-run
```

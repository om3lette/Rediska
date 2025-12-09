# Rediska

## Installation

### vcpkg

```bash
git clone --branch 2025.10.17 --depth 1 https://github.com/microsoft/vcpkg.git && \
cd vcpkg && \
./bootstrap-vcpkg.sh && \
./vcpkg install
```

### Project build

```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=scripts/buildsystems/vcpkg.cmake && \
cmake --build rediska -j $(nproc)
```

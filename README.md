# Rediska

## Building from source

### vcpkg

> [!NOTE]
> Add `--triplet x64-linux-release` to the vcpkg install to build dependencies in release.
> Replace `linux` with your OS if it is supported

```bash
git clone --branch 2025.10.17 --depth 1 https://github.com/microsoft/vcpkg.git && \
./vcpkg/bootstrap-vcpkg.sh && \
./vcpkg/vcpkg install
```

### Project build

```bash
export REDISKA_BUILD_DIR=cmake-build-debug && \
cmake -S . -B ${REDISKA_BUILD_DIR} -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake && \
cmake --build ${REDISKA_BUILD_DIR} -j $(nproc)
```

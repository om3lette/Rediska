# Creating a test group

1. **Create a new test file** \
    Place it under `/tests/frontend/` or `/tests/backend/`, following the [naming convention](#naming-convention) below.

2. **Include the testing framework**  \
    Add the following at the top of the file:
    ```C++
    #include <doctest/doctest.h>
    ```

3. **Register the file in the build system** \
   Add the new test file to `/tests/CMakeLists.txt` so it’s compiled and executed as part of the test suite.

4. **Start writing tests!** \
   See [doctest docs](https://github.com/doctest/doctest/blob/master/doc/markdown/readme.md) for more details.

# Naming convention

File name should match against the following pattern:

`<module>_<feature>_<test_type>_tests.cpp`

Where:
- `<module>` - the component or subsystem under test.
  - Backend modules:  `cache` | `worker`
  - Frontend modules: `work in progress`
- `<feature>` - a concise, kebab-case description of the specific functionality.  
- `<test_type>` - one of the following:
  - `unit`
  - `integration`
  - `e2e`

# Examples

| Path                                           | Description                                                    |
| :--------------------------------------------- | :------------------------------------------------------------- |
| `backend/cache_lru_unit_tests.cpp`             | Unit tests for LRU eviction logic in the cache module          |
| `backend/worker_handle-request_unit_tests.cpp` | Unit tests for the request-handling logic in the worker module |

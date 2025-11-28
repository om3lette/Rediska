## Новая группа тестов

1. Создайте новый файл, отображающий назначение тестов, которые он содержит.
2. Вставьте необходимые заголовки тестирующей системы

```C++
#include <doctest/doctest.h>
```

3. Добавьте файл в `/tests/CMakeLists.txt` 
4. Теперь вы готовы приступить к написанию тестов! 


## Пример тестового файла

```C++
#include <doctest/doctest.h>

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

TEST_CASE("testing the factorial function") {
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}
```

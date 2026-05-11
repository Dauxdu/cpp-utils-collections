# cpp-utils-collections

```cmake
include(FetchContent)
FetchContent_Declare(cpp_utils
    GIT_REPOSITORY https://github.com/Dauxdu/cpp-utils-collections.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cpp_utils)
```

### InputNumeric example (`inx:numeric`)

Базовая функция парсинга. Выбрасывает исключения при ошибке, поэтому управление циклом повтора лежит на пользователе.

```cpp
import std;
import inx;

int main()
{
    int value{};
    while (true)
    {
        try
        {
            std::print("Enter a number (0): ");
            // Парсит строку
            // Диапазон [0, 0] означает, что принимается только ноль
            value = inx::input_numeric<int>(0, 0);
            break;
        }
        catch (const std::exception &e)
        {
            std::println("Error: {}", e.what());
            continue;
        }
    }

    std::println("Parsed: {}", value);
    return 0;
}
```

### InputPromptNumeric example (`inx:numericInteractive`)

Обёртка с интерактивным вводом. **Содержит встроенный цикл повтора** до успешного ввода.

```cpp
import std;
import inx;

int main()
{
    // Функция сама выведет промпт и будет запрашивать ввод, пока не получит валидное число
    int value = inx::input_prompt_numeric<int>("Enter a number (0): ", 0, 0);
    std::println("Parsed: {}", value);
    return 0;
}
```

## TODO

### Input

- Fix new line issue
- InputString
- InputConfirm
- Tests

### Command

- Examples
- Tests

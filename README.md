# cpp-utils-collections

```cmake
include(FetchContent)
FetchContent_Declare(cpp_utils
    GIT_REPOSITORY https://github.com/Dauxdu/cpp-utils-collections.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cpp_utils)
```

### `inx::input_numeric` example

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

### `inx::input_prompt_numeric` example

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

### `inx::input_string` example

```cpp
import std;
import inx;

int main()
{
    try
    {
        // Валидация имени с помощью регулярного выражения без цикла
        std::print("Enter name (letters only): ");
        std::string name = inx::input_string(std::regex{R"([A-Za-z]+)"}); // Только буквы
        std::println("Hello, {}!", name);
    }
    catch (const std::exception &e)
    {
        std::println("Error: {}", e.what());
    }

    return 0;
}
```

### `inx::input_prompt_string` example

```cpp
import std;
import inx;

int main()
{
    // Валидация кода регулярным выражением с циклом
    std::string code = inx::input_prompt_string("Enter 3-10 digit code: ", std::regex{R"(\d{3,10})"}); // Только 3-10 цифр
    std::println("Code accepted: {}", code);

    // Валидация email строковым литералом с циклом
    std::string email = inx::input_prompt_string("Enter Email: ", R"([A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,})"); // Паттерн Email
    std::println("Email: {}", email);

    return 0;
}
```

## TODO

### Input

- Fix new line issue
- InputConfirm
- Tests

### Command

- Examples
- Tests

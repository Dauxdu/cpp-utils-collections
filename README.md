# 🛠️ cpp-utils-collections

[![Статус сборки](https://github.com/Dauxdu/cpp-utils-collections/actions/workflows/on-push.yml/badge.svg)](https://github.com/Dauxdu/cpp-utils-collections/actions)
[![Стандарт C++](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support/23)
[![CMake](https://img.shields.io/badge/CMake-4.2-blue.svg)](https://cmake.org/)

---

## Возможности

### Модуль ввода (`inx`)

- **`input_numeric<T>`** — Типобезопасный ввод чисел с проверкой диапазона
  - Поддержка всех арифметических типов (`int`, `double` и др.)
  - Проверка границ с настраиваемыми мин/макс значениями
- **`input_string`** — Валидация строк через регулярные выражения
  - Принимает `std::regex` или строковые литералы с паттерном

### Модуль команд (`cmd`)

- **Реализация паттерна Команда** — Поддержка отмены/повтора для операций с контейнерами
- **`CommandHistory`** — Управление стеком команд с настраиваемой глубиной
  - `Execute()`, `Undo()`, `Redo()` с поддержкой множественных шагов
  - `CanUndo()`, `CanRedo()`, инспекция истории
- **Готовые команды**: `Insert`, `Erase`, `Update`, `Swap`, `Clear`
- **На основе шаблонов** — Работает с любым `std::vector<T>`

---

## Подключение

### Через CMake FetchContent (Рекомендуется)

```cmake
cmake_minimum_required(VERSION 4.2)
project(awesome LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD 451f2fe2-a8a2-47c3-bc32-94786d8fc91b)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8 /W4)
endif()

include(FetchContent)
FetchContent_Declare(cpp_utils
    GIT_REPOSITORY https://github.com/Dauxdu/cpp-utils-collections.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cpp_utils)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    inx
    cmd
)
```

---

## Обзор модулей

### InputNumeric

```cpp
import std;
import inx;

// Базовое использование — выбрасывает исключение при ошибке
int main()
{
	try
	{
		std::print("Введите возраст (18-65): ");
		int age = inx::input_numeric<int>(18, 65);
		std::println("Возраст: {}", age);
	}
	catch (const std::runtime_error &e)
	{
		std::println("Ошибка: {}", e.what());
		throw;
	}
	catch (const std::exception &e)
	{
		std::println("Ошибка: {}", e.what());
	}

    return 0;
}
```

```cpp
import std;
import inx;

// Интерактивный режим — автоповтор до успешного ввода
int main()
{
	// Функция сама выводит подсказку и запрашивает ввод, пока не получит валидное число
	double price = inx::input_numeric<double>("Введите цену (0.01-9999.99): ", 0.01, 9999.99);
	std::println("Цена установлена: ${:.2f}", price);

    return 0;
}
```

### InputString

```cpp
import std;
import inx;

int main()
{
	// Валидация имени: только буквы
	std::string name = inx::input_string(
		"Введите имя пользователя: ",
		std::regex{R"([A-Za-z][A-Za-z0-9_]*)"});

	// Валидация email через строковый паттерн
	std::string email = inx::input_string(
		"Введите email: ",
		R"([A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,})");

	std::println("Пользователь: {} <{}>", name, email);

    return 0;
}
```

---

### Command

Реализация паттерна Команда с поддержкой отмены/повтора для операций над `std::vector<T>`.

#### Команды

| Команда     | Описание                         |
| ----------- | -------------------------------- |
| `Insert<T>` | Вставка элемента(ов) по индексу  |
| `Erase<T>`  | Удаление элемента(ов) по индексу |
| `Update<T>` | Замена элемента по индексу       |
| `Swap<T>`   | Обмен элементов по двум индексам |
| `Clear<T>`  | Очистка всего контейнера         |

#### Пример использования

```cpp
import std;
import cmd;

int main()
{
    cmd::Context<int> ctx;
    cmd::CommandHistory history{10}; // Хранит последние 10 команд

    try
    {
        // Выполнение команд
        history.Execute(std::make_unique<cmd::Insert<int>>(ctx, 0, 42));
        history.Execute(std::make_unique<cmd::Insert<int>>(ctx, 1, 100));

        std::println("Данные: {}", ctx.data); // [42, 100]

        // Отмена последней операции
        if (history.CanUndo())
        {
            history.Undo();                             // Удаляет 100
            std::println("После отмены: {}", ctx.data); // [42]
        }

        // Повтор
        if (history.CanRedo())
        {
            history.Redo(); // Восстанавливает 100
        }
    }
    catch (const std::exception &e)
    {
        std::println("Ошибка команды: {}", e.what());
    }

    return 0;
}
```

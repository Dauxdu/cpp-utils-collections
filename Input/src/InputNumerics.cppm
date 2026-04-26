/**
 * @file InputNumerics.cppm
 * @brief Модуль безопасного ввода и валидации числовых типов.
 * @details Предоставляет типобезопасный консольный ввод с проверкой диапазона,
 *          поддержкой кастомных политик обработки ошибок и независимостью от локали.
 *          Использует C++23 модули и std::from_chars для быстрого парсинга.
 * @author CherryJell & Dauxdu
 * @date 2026
 */
export module nin;

import std;

export namespace nin
{
    /**
     * @brief Концепт, ограничивающий шаблон арифметическими типами, исключая `bool`.
     * @tparam ValueT Проверяемый тип.
     * @details Гарантирует, что параметр шаблона является числовым (целым или вещественным),
     *          но не булевым, что предотвращает неочевидные преобразования при вводе
     */
    template <typename ValueT>
    concept NumericType = std::is_arithmetic_v<ValueT> && !std::is_same_v<ValueT, bool>;

    /**
     * @brief Удаляет ведущие и завершающие пробельные символы из строки.
     * @param raw_str Исходное представление строки.
     * @return std::string_view Подстрока без пробелов.
     * @details Работает за O(N), не выполняет динамических аллокаций.
     *          Возвращает пустой `string_view`, если строка состоит только из пробелов.
     */
    [[nodiscard]] constexpr std::string_view trim(std::string_view raw_str)
    {
        auto start = raw_str.find_first_not_of(" \t\n\r\f\v");
        if (start == std::string_view::npos)
        {
            return {};
        }
        auto end = raw_str.find_last_not_of(" \t\n\r\f\v");
        return raw_str.substr(start, end - start + 1);
    }

    /**
     * @brief Стандартная политика обработки ошибок ввода.
     * @tparam NumT Тип проверяемого числа.
     * @details Выводит сообщения в стандартный вывод. Может быть заменена пользовательской политикой
     *          для логирования, кастомизации сообщений.
     */
    template <NumericType NumT>
    struct ErrorPolicy
    {
        /** @brief Вызывается при пустом вводе или вводе только пробельных символов. */
        static void report_empty() { std::println("nin::input_numeric: empty input."); }

        /** @brief Вызывается при наличии недопустимых символов в начале строки. */
        static void report_invalid() { std::println("nin::input_numeric: invalid numeric format."); }

        /** @brief Вызывается при переполнении типа (например, ввод числа, выходящего за пределы `int`). */
        static void report_out_of_range() { std::println("nin::input_numeric: value out of type range."); }

        /** @brief Вызывается при наличии мусора после корректного числа. */
        static void report_trailing() { std::println("nin::input_numeric: trailing characters detected."); }

        /**
         * @brief Вызывается при выходе значения за пользовательский диапазон.
         * @param min Нижняя граница допустимого диапазона.
         * @param max Верхняя граница допустимого диапазона.
         */
        static void report_bounds(NumT min, NumT max)
        {
            std::println("nin::input_numeric: value out of range [{}, {}].", min, max);
        }
    };

    /**
     * @brief Безопасный интерактивный ввод числа с валидацией диапазона и формата.
     * @tparam NumericT Арифметический тип возвращаемого значения (проверяется через `NumericType`).
     * @tparam Error Политика обработки ошибок ввода (по умолчанию `nin::ErrorPolicy<NumericT>`).
     * @param prompt Текст запроса, выводимый перед ожиданием ввода. Если пустой, запрос не выводится.
     * @param min_value Минимально допустимое значение (включительно). По умолчанию: `std::numeric_limits::lowest()`.
     * @param max_value Максимально допустимое значение (включительно). По умолчанию: `std::numeric_limits::max()`.
     * @param in Поток ввода. По умолчанию: `std::cin`.
     * @return NumericT Валидированное числовое значение, находящееся в диапазоне `[min_value, max_value]`.
     * @throws std::runtime_error Если поток ввода переходит в состояние ошибки или закрывается (EOF).
     * @details Функция использует `std::from_chars` для быстрого и независимого от локали парсинга.
     *          Для подстановки переменных в строку рекомендуется использовать `std::format`
     *          при формировании строки запроса: `std::format("prompt {}: ", var)`.
     * @note Требует поддержки `std::from_chars` для плавающей точки (C++23).
     */
    template <NumericType NumericT, typename Error = ErrorPolicy<NumericT>>
    NumericT input_numeric(std::string_view prompt,
                           NumericT min_value = std::numeric_limits<NumericT>::lowest(),
                           NumericT max_value = std::numeric_limits<NumericT>::max(),
                           std::istream &in = std::cin,
                           std::ostream &out = std::cout)
    {

        std::string line;
        while (true)
        {
            if (!prompt.empty())
            {
                out << prompt << std::flush;
            }

            if (!std::getline(in, line))
            {
                throw std::runtime_error("nin::input_numeric: input stream failure.");
            }

            const auto trimmed = trim(line);
            if (trimmed.empty())
            {
                Error::report_empty();
                continue;
            }

            NumericT value{};
            const auto [ptr, error] = std::from_chars(trimmed.begin(), trimmed.end(), value);

            if (error == std::errc::invalid_argument)
            {
                Error::report_invalid();
            }
            else if (error == std::errc::result_out_of_range)
            {
                Error::report_out_of_range();
            }
            else if (ptr != trimmed.end())
            {
                Error::report_trailing();
            }
            else if (value < min_value || value > max_value)
            {
                Error::report_bounds(min_value, max_value);
            }
            else
            {
                return value;
            }
        }
    }
}
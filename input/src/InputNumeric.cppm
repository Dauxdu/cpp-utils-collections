/**
 * @file InputNumeric.cppm
 * @brief Модуль безопасного ввода и валидации числовых типов.
 * @details Предоставляет типобезопасный консольный ввод с проверкой диапазона.
 * @author CherryJell & Dauxdu
 * @date 2026
 */
export module inx:numeric;

import std;
import :helper;

export namespace inx
{
    template <typename TValue>
    concept NumericType = std::is_arithmetic_v<TValue> && !std::is_same_v<TValue, bool>;

    template <NumericType TNumeric>
    [[nodiscard]] TNumeric input_numeric(TNumeric min_value = std::numeric_limits<TNumeric>::lowest(),
                                         TNumeric max_value = std::numeric_limits<TNumeric>::max(),
                                         std::istream &in = std::cin)
    {
        std::string line;
        TNumeric value{};
        std::from_chars_result result;

        if (!std::getline(in, line))
        {
            throw std::runtime_error("inx::input_numeric: input stream failure");
        }

        const auto trimmed = inx::trim(line);
        if (trimmed.empty())
        {
            throw std::invalid_argument("inx::input_numeric: empty input");
        }

        if (min_value > max_value)
        {
            throw std::invalid_argument("inx::input_numeric: min_value > max_value");
        }

        if constexpr (std::integral<TNumeric>)
        {
            result = std::from_chars(trimmed.begin(), trimmed.end(), value);
        }
        else if constexpr (std::floating_point<TNumeric>)
        {
            result = std::from_chars(trimmed.begin(), trimmed.end(), value, std::chars_format::general);
        }

        if (result.ec == std::errc::invalid_argument)
        {
            throw std::invalid_argument("inx::input_numeric: invalid numeric format");
        }

        if (result.ec == std::errc::result_out_of_range)
        {
            throw std::out_of_range("inx::input_numeric: value out of type range");
        }

        if (result.ptr != trimmed.data() + trimmed.size())
        {
            throw std::invalid_argument("inx::input_numeric: trailing characters detected");
        }

        if (value < min_value || value > max_value)
        {
            throw std::out_of_range(std::format("inx::input_numeric: value out of range [{}, {}]", min_value, max_value));
        }

        return value;
    }

    template <NumericType T>
    [[nodiscard]] T input_prompt_numeric(const std::string &prompt,
                                         T min_value = std::numeric_limits<T>::lowest(),
                                         T max_value = std::numeric_limits<T>::max(),
                                         std::ostream &out = std::cout, std::istream &in = std::cin)
    {
        while (true)
        {
            try
            {
                out << prompt << std::flush;
                return input_numeric<T>(min_value, max_value, in);
            }
            catch (const std::exception &e)
            {
                out << e.what() << '\n';
                continue;
            }
        }
    }
}

/**
 * @file InputNumeric.cppm
 * @brief Модуль безопасного ввода и валидации числовых типов.
 * @details Предоставляет типобезопасный консольный ввод с проверкой диапазона.
 * @author CherryJell & Dauxdu
 * @date 2026
 */
export module nin;

import std;

export namespace nin
{
    template <typename ValueT>
    concept NumericType = std::is_arithmetic_v<ValueT> && !std::is_same_v<ValueT, bool>;

    [[nodiscard]] constexpr std::string_view trim(std::string_view raw_str) noexcept
    {
        constexpr std::string_view whitespace = " \t\n\r\f\v";
        auto start = raw_str.find_first_not_of(whitespace);
        if (start == std::string_view::npos)
        {
            return {};
        }
        auto end = raw_str.find_last_not_of(whitespace);
        return raw_str.substr(start, end - start + 1);
    }

    template <NumericType NumericT>
    [[nodiscard]] NumericT input_numeric(NumericT min_value = std::numeric_limits<NumericT>::min(),
                                         NumericT max_value = std::numeric_limits<NumericT>::max(),
                                         std::istream &in = std::cin)
    {
        std::string line;
        if (!std::getline(in, line))
        {
            throw std::runtime_error("nin::input_numeric: input stream failure.");
        }

        const auto trimmed = trim(line);
        if (trimmed.empty())
        {
            throw std::invalid_argument("nin::input_numeric: empty input.");
        }

        if (min_value > max_value)
        {
            throw std::invalid_argument("nin::input_numeric: min_value > max_value.");
        }

        NumericT value{};
        std::from_chars_result result;

        if constexpr (std::integral<NumericT>)
        {
            result = std::from_chars(trimmed.begin(), trimmed.end(), value);
        }
        else if constexpr (std::floating_point<NumericT>)
        {
            result = std::from_chars(trimmed.begin(), trimmed.end(), value, std::chars_format::general);
        }

        if (result.ec == std::errc::invalid_argument)
        {
            throw std::invalid_argument("nin::input_numeric: invalid numeric format.");
        }

        if (result.ec == std::errc::result_out_of_range)
        {
            throw std::out_of_range("nin::input_numeric: value out of type range.");
        }

        if (result.ptr != trimmed.end())
        {
            throw std::invalid_argument("nin::input_numeric: trailing characters detected.");
        }

        if (value < min_value || value > max_value)
        {
            throw std::out_of_range(std::format("nin::input_numeric: value out of range [{}, {}].", min_value, max_value));
        }

        return value;
    }
}
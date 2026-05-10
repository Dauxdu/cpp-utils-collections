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
    template <typename ValueT>
    concept NumericType = std::is_arithmetic_v<ValueT> && !std::is_same_v<ValueT, bool>;

    template <NumericType NumericT>
    [[nodiscard]] NumericT input_numeric(NumericT min_value = std::numeric_limits<NumericT>::min(),
                                         NumericT max_value = std::numeric_limits<NumericT>::max(),
                                         std::istream &in = std::cin)
    {
        std::string line;
        if (!std::getline(in, line))
        {
            throw std::runtime_error("inx::input_numeric: input stream failure.");
        }

        const auto trimmed = inx::trim(line);
        if (trimmed.empty())
        {
            throw std::invalid_argument("inx::input_numeric: empty input.");
        }

        if (min_value > max_value)
        {
            throw std::invalid_argument("inx::input_numeric: min_value > max_value.");
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
            throw std::invalid_argument("inx::input_numeric: invalid numeric format.");
        }

        if (result.ec == std::errc::result_out_of_range)
        {
            throw std::out_of_range("inx::input_numeric: value out of type range.");
        }

        if (result.ptr != trimmed.data() + trimmed.size())
        {
            throw std::invalid_argument("inx::input_numeric: trailing characters detected.");
        }

        if (value < min_value || value > max_value)
        {
            throw std::out_of_range(std::format("inx::input_numeric: value out of range [{}, {}].", min_value, max_value));
        }

        return value;
    }
}
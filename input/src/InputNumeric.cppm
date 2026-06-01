export module inx:numeric;

import std;
import :helper;

export namespace inx
{
    template <typename TValue>
    [[nodiscard]]
    TValue input_numeric(TValue min_value = std::numeric_limits<TValue>::lowest(),
                         TValue max_value = std::numeric_limits<TValue>::max(),
                         std::istream &in = std::cin)
    {

        if (min_value > max_value)
        {
            throw std::logic_error("inx::input_numeric: min_value > max_value");
        }

        TValue value{};
        std::string line;
        if (!std::getline(in, line))
        {
            throw std::runtime_error("inx::input_numeric: input stream failure");
        }

        const std::string trimmed = inx::trim(line);
        if (trimmed.empty())
        {
            throw std::invalid_argument("inx::input_numeric: empty input");
        }

        const char *begin = trimmed.data();
        const char *end = trimmed.data() + trimmed.size();

        std::from_chars_result result{};
        if constexpr (std::integral<TValue>)
        {
            result = std::from_chars(begin, end, value);
        }
        else if constexpr (std::floating_point<TValue>)
        {
            result = std::from_chars(begin, end, value);
        }

        if (result.ec == std::errc::invalid_argument)
        {
            throw std::invalid_argument("inx::input_numeric: invalid numeric format");
        }

        if (result.ec == std::errc::result_out_of_range)
        {
            throw std::out_of_range("inx::input_numeric: value out of type range");
        }

        if (result.ptr != end)
        {
            throw std::invalid_argument("inx::input_numeric: trailing characters detected");
        }

        if (value < min_value || value > max_value)
        {
            throw std::out_of_range(std::format("inx::input_numeric: value out of range [{}, {}]", min_value, max_value));
        }

        return value;
    }

    template <typename TValue>
    [[nodiscard]]
    TValue input_numeric(const std::string &prompt,
                         TValue min_value = std::numeric_limits<TValue>::lowest(),
                         TValue max_value = std::numeric_limits<TValue>::max(),
                         std::istream &in = std::cin, std::ostream &out = std::cout)
    {
        while (true)
        {
            try
            {
                out << prompt;
                return input_numeric<TValue>(min_value, max_value, in);
            }
            catch (const std::runtime_error &error)
            {
                out << error.what() << '\n';
                throw;
            }
            catch (const std::exception &error)
            {
                out << error.what() << '\n';
            }
        }
    }
}
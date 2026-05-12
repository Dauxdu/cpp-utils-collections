export module inx:numericInteractive;

import std;
import :numeric;

export namespace inx
{
    template <NumericType T>
    [[nodiscard]] T input_prompt_numeric(const std::string &prompt,
                                         T min_value = std::numeric_limits<T>::lowest(),
                                         T max_value = std::numeric_limits<T>::max(),
                                         std::ostream &out = std::cout,
                                         std::istream &in = std::cin)
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
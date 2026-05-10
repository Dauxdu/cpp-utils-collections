module inx:helper;

import std;

namespace inx
{
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
}
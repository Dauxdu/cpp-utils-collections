module inx:helper;

import std;

namespace inx
{
    [[nodiscard]] std::string trim(const std::string &raw_str)
    {
        const std::string whitespace = " \t\n\r\f\v";
        auto start = raw_str.find_first_not_of(whitespace);
        if (start == std::string::npos)
        {
            return {};
        }
        auto end = raw_str.find_last_not_of(whitespace);
        return raw_str.substr(start, end - start + 1);
    }
}
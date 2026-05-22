/**
 * @file InputString.cppm
 * @brief Модуль безопасного ввода и валидации строковых типов.
 * @details Предоставляет типобезопасный консольный ввод с проверкой по регулярному выражению.
 * @author CherryJell & Dauxdu
 * @date 2026
 */
export module inx:string;

import std;
import :helper;

export namespace inx
{
    [[nodiscard]] std::string input_string(const std::regex &pattern, std::istream &in = std::cin)
    {
        std::string line;

        if (!std::getline(in, line))
        {
            throw std::runtime_error("inx::input_string: input stream failure");
        }

        const std::string trimmed = inx::trim(line);

        const char *begin = trimmed.data();
        const char *end = trimmed.data() + trimmed.size();

        if (trimmed.empty())
        {
            throw std::invalid_argument("inx::input_string: empty input");
        }

        if (!std::regex_match(begin, end, pattern))
        {
            throw std::invalid_argument(std::format("inx::input_string: input '{}' does not match required pattern", trimmed));
        }

        return trimmed;
    }

    /**
     * @brief Перегрузка input_string для строковых литералов-шаблонов.
     */
    [[nodiscard]] std::string input_string(const std::string &pattern, std::istream &in = std::cin)
    {
        const std::regex pattern_str{pattern};

        return input_string(pattern_str, in);
    }

    [[nodiscard]] std::string input_string(const std::string &prompt, const std::regex &pattern,
                                           std::istream &in = std::cin, std::ostream &out = std::cout)
    {
        while (true)
        {
            try
            {
                out << prompt;
                return input_string(pattern, in);
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

    /**
     * @brief Перегрузка input_prompt_string для строковых литералов-шаблонов.
     */
    [[nodiscard]] std::string input_string(const std::string &prompt, const std::string &pattern,
                                           std::istream &in = std::cin, std::ostream &out = std::cout)
    {
        const std::regex pattern_str{pattern};

        return input_string(prompt, pattern_str, in, out);
    }
}
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
    template <typename T>
    concept StringType = std::same_as<std::remove_cvref_t<T>, std::string> || std::same_as<std::remove_cvref_t<T>, std::string_view>;

    template <StringType TString = std::string>
    [[nodiscard]] TString input_string(const std::regex &pattern, std::istream &in = std::cin)
    {
        std::string line;

        if (!std::getline(in, line))
        {
            throw std::runtime_error("inx::input_string: input stream failure");
        }

        const auto trimmed = inx::trim(line);

        if (trimmed.empty())
        {
            throw std::invalid_argument("inx::input_string: empty input");
        }

        if (!std::regex_match(trimmed.begin(), trimmed.end(), pattern))
        {
            throw std::invalid_argument(std::format("inx::input_string: input '{}' does not match required pattern", trimmed));
        }

        return TString{trimmed};
    }

    /**
     * @brief Перегрузка input_string для строковых литералов-шаблонов.
     */
    template <StringType TString = std::string>
    [[nodiscard]] TString input_string(std::string_view pattern_str, std::istream &in = std::cin)
    {
        const std::regex pattern{std::string{pattern_str}};
        {
            return input_string<TString>(pattern, in);
        }
    }

    template <StringType TString = std::string>
    [[nodiscard]] TString input_string(std::string_view prompt, const std::regex &pattern,
                                       std::istream &in = std::cin, std::ostream &out = std::cout)
    {
        while (true)
        {
            try
            {
                out << prompt;
                out.flush();

                return input_string<TString>(pattern, in);
            }
            catch (const std::invalid_argument &e)
            {
                out << "Error: " << e.what() << '\n';
                continue;
            }
            catch (const std::runtime_error &e)
            {
                throw;
            }
        }
    }

    /**
     * @brief Перегрузка input_prompt_string для строковых литералов-шаблонов.
     */
    template <StringType TString = std::string>
    [[nodiscard]] TString input_string(std::string_view prompt, std::string_view pattern,
                                       std::istream &in = std::cin, std::ostream &out = std::cout)
    {
        const std::regex pattern_str{std::string{pattern}};
        {
            return input_string<TString>(prompt, pattern_str, in, out);
        }
    }
}
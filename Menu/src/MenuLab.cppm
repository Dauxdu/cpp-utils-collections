export module MenuLab;

import std;

export template <typename CmdT>
class Menu
{
private:
	std::size_t _lab_num = 0;
	std::string _author;
	std::size_t _variant = 0;
	std::unordered_map<std::size_t, std::string> _options;

public:
	explicit Menu(std::size_t lab_num,
				  std::string author,
				  std::size_t variant,
				  std::unordered_map<std::size_t, std::string> options)
		: _lab_num(lab_num),
		  _author(std::move(author)),
		  _variant(variant),
		  _options(options)
	{
	}

	void PrintHeader() const
	{
		std::println("");
		std::println("------------------------------");
		std::println("Лабораторная работа №: {}", _lab_num);
		std::println("Автор: {}", _author);
		std::println("Вариант №: {}", _variant);
		std::println("------------------------------");
		std::println("");
	}

	void PrintMenu() const
	{
		std::println("");
		std::println("------------------------------------------------------------------------------------------------------------------------");
		for (const auto &[index, option] : _options)
		{
			std::println("[{}] {}", index, option);
		}
		std::println("------------------------------------------------------------------------------------------------------------------------");
		std::println("");
	}
};
export module MenuLab;

import std;
import nin;

// ... --- ...

export struct menu_item {
    std::string name;
    std::function<void()> action;

    template<typename F>
    menu_item(std::string n, F&& f)
        : name(std::move(n)),
          action(std::forward<F>(f)) {}
};

export class Menu {
private:
    int _lab_num{};
    std::string _author;
    int _variant{};
    std::vector<menu_item> _items;

public:
    Menu(int lab_num,
         std::string author,
         int variant,
         std::vector<menu_item> items)
        : _lab_num(lab_num),
          _author(std::move(author)),
          _variant(variant),
          _items(std::move(items))
    {}

    template<typename F>
    void add_item(std::string name, F&& f) {
        _items.emplace_back(std::move(name), std::forward<F>(f));
    }

    void add_item(menu_item item) {
        _items.emplace_back(std::move(item));
    }

    void print_header() const {
        std::println("\n------------------------------");
        std::println("Лабораторная работа №: {}", _lab_num);
        std::println("Автор: {}", _author);
        std::println("Вариант №: {}", _variant);
        std::println("------------------------------\n");
    }

    void run() {
        if (_items.empty()) {
            std::println("Меню пустое");
            return;
        }

        while (true) {
            for (std::size_t i = 0; i < _items.size(); ++i) {
                std::println("[{}] {}", i + 1, _items[i].name);
            }
            std::println("[0] Выход");

            int choice = nin::input_numeric<int>(
                "Выбор: ",
                0,
                static_cast<int>(_items.size())
            );

            if (choice == 0) {
                return;
            }

            auto& item = _items[choice - 1];

            try {
                item.action();
            }
            catch (const std::exception& e) {
                std::println("Ошибка: {}", e.what());
            }
        }
    }
};

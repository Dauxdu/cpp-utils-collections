export module MenuLab;
import std;

//👍👍👍👍👍👍👍👍👍👍👍👍
/*
import nin;
struct SafeInputPolicy {
    static size_t GetChoice(std::string_view prompt, size_t min, size_t max) {
        return nin::input_numeric<size_t>(prompt, min, max);
    }
};
using MyMenu = Menu<SafeInputPolicy, DefaultOutputPolicy>;
*/

//👎👎👎
export struct DefaultInputPolicy {
    static std::size_t GetChoice(std::string_view prompt, std::size_t min, std::size_t max) {
        if (!prompt.empty()) std::print("{} ", prompt);
        
        std::size_t value;
        
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("DefaultInputPolicy: invalid input");
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (value < min || value > max) {
            throw std::runtime_error("DefaultInputPolicy: value out of range");
        }
        
        return value;
    }
};

export struct DefaultOutputPolicy {
    static void Print(std::string_view s) { std::print("{}",s); }
    static void Println(std::string_view s) { std::println("{}",s); }
    static void Println() { std::println(); }
};

export struct ICommand {
    virtual ~ICommand() = default;
    virtual void Execute() const = 0;
};

export struct MenuItemReading {
    std::string Name;
    std::string Value;
};

export struct MenuItemExecutable {
    std::string Name;
    std::unique_ptr<ICommand> Action;

    MenuItemExecutable(std::string n, std::unique_ptr<ICommand> cmd)
        : Name(std::move(n)), Action(std::move(cmd)) {}
};

namespace detail {
    template<typename Func>
    struct CallableCommand final : ICommand {
        Func func;
        explicit CallableCommand(Func f) : func(std::move(f)) {}
        void Execute() const override { func(); }
    };
}

export template<typename InputPolicy = DefaultInputPolicy, 
                typename OutputPolicy = DefaultOutputPolicy>
class Menu {
private:
    std::vector<MenuItemReading> _readonly;
    std::vector<MenuItemExecutable> _executable;

public:
    Menu() = default;

    Menu(std::vector<MenuItemReading> ro, std::vector<MenuItemExecutable> ex)
        : _readonly(std::move(ro)), _executable(std::move(ex)) {}

    void AddReadonly(std::string name, std::string value) {
        _readonly.push_back({std::move(name), std::move(value)});
    }

    void AddExecutable(std::string name, std::unique_ptr<ICommand> cmd) {
        _executable.emplace_back(std::move(name), std::move(cmd));
    }

    template<typename Func>
    void AddExecutable(std::string name, Func&& f) {
        _executable.emplace_back(
            std::move(name),
            std::make_unique<detail::CallableCommand<std::decay_t<Func>>>(std::forward<Func>(f))
        );
    }

    void ShowHeader() const noexcept {
        if (_readonly.empty()) return;
        OutputPolicy::Println("\n------------------------------");
        for (const auto& item : _readonly) {
            OutputPolicy::Println(item.Name + ": " + item.Value);
        }
        OutputPolicy::Println("------------------------------\n");
    }

    void ShowActions() const noexcept {
        if (_executable.empty()) {
            OutputPolicy::Println("Нет действий.");
            return;
        }
        for (std::size_t i = 0; i < _executable.size(); ++i) {
            OutputPolicy::Println("[" + std::to_string(i + 1) + "] " + _executable[i].Name);
        }
        OutputPolicy::Println("[0] Выход");
    }

    int Step() {
        if (_executable.empty()) {
            OutputPolicy::Println("Нет действий. Завершение.");
            return 1;
        }

        ShowHeader();
        ShowActions();

        try {
            std::size_t choice = InputPolicy::GetChoice("Выбор: ", 0, _executable.size());
        
            if (choice == 0) {
                OutputPolicy::Println("Выход.");
                return 1;
            }

            _executable[choice - 1].Action->Execute();
        } catch (const std::exception& e) {
            OutputPolicy::Println("Ошибка: " + std::string(e.what()));
        }
        OutputPolicy::Println();
        return 0;
    }
};

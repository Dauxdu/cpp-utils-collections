export module ICommand;

import std;

export namespace cmd
{
    template <typename ContextT>
    struct Context
    {
        std::vector<ContextT> data;
    };

    class ICommand
    {
    protected:
        ICommand() = default;

    public:
        virtual ~ICommand() = default;

        ICommand(const ICommand &) = delete;
        ICommand(ICommand &&) = delete;
        ICommand &operator=(const ICommand &) = delete;
        ICommand &operator=(ICommand &&) = delete;

        virtual void Execute() = 0;
        virtual void Undo() = 0;
        [[nodiscard]] virtual std::string Description() const = 0;
    };
}
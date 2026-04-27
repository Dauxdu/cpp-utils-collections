export module ICommand;

import std;

export namespace cmd
{
    template <typename ContextT>
    struct Context
    {
        std::vector<ContextT> data{};
    };

    template <typename ContextT>
    class ICommand
    {
    protected:
        ICommand() = default;

    public:
        virtual ~ICommand() = default;

        ICommand(const ICommand &) = delete;

        ICommand &operator=(const ICommand &) = delete;

        virtual void Execute(Context<ContextT> &ctx) = 0;

        virtual void Undo(Context<ContextT> &ctx) = 0;

        [[nodiscard]]
        virtual std::string Description() const = 0;
    };
}
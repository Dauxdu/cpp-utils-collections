export module CommandSwap;

import std;
import ICommand;

export namespace cmd
{
    template <typename ContextT>
    class Swap final : public ICommand
    {
    private:
        Context<ContextT> &_ctx;
        std::size_t _index_1 = 0;
        std::size_t _index_2 = 0;
        std::string _description;

    public:
        Swap(Context<ContextT> &ctx, std::size_t index_1, std::size_t index_2) : _ctx(ctx), _index_1(index_1), _index_2(index_2)
        {
            if (index_1 >= ctx.data.size() || index_2 >= ctx.data.size())
            {
                throw std::out_of_range("cmd::Swap: index out of range");
            }
            _description = std::format("Swap element at index {} with element at index {}", index_1, index_2);
        }

        void Execute() override
        {
            if (_index_1 == _index_2)
            {
                return;
            }
            std::swap(_ctx.data[_index_1], _ctx.data[_index_2]);
        }

        void Undo() override
        {
            Execute();
        }

        [[nodiscard]]
        std::string Description() const override
        {
            return _description;
        }
    };
}
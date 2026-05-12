export module cmd:CommandSwap;

import std;
import :ICommand;

export namespace cmd
{
    template <typename ContextT>
    class Swap final : public ICommand
    {
    private:
        Context<ContextT> &_ctx;
        std::size_t _item_index_1 = 0;
        std::size_t _item_index_2 = 0;
        std::string _description;

    public:
        Swap(Context<ContextT> &ctx, std::size_t item_index_1, std::size_t item_index_2) : _ctx(ctx), _item_index_1(item_index_1), _item_index_2(item_index_2)
        {
            if (item_index_1 >= ctx.data.size() || item_index_2 >= ctx.data.size())
            {
                throw std::out_of_range("cmd::Swap: index out of range");
            }
            _description = std::format("Swap element at index {} with element at index {}", item_index_1, item_index_2);
        }

        void Execute() override
        {
            if (_item_index_1 == _item_index_2)
            {
                return;
            }
            std::swap(_ctx.data[_item_index_1], _ctx.data[_item_index_2]);
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
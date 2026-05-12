export module cmd:CommandErase;

import std;
import :ICommand;

export namespace cmd
{
	template <typename ContextT>
	class Erase final : public ICommand
	{
	private:
		Context<ContextT> &_ctx;
		std::size_t _index = 0;
		ContextT _value;
		std::string _description;

	public:
		Erase(Context<ContextT> &ctx, std::size_t index) : _ctx(ctx), _index(index)
		{
			if (index >= ctx.data.size())
			{
				throw std::out_of_range("cmd::Erase: index out of range");
			}
			_description = std::format("Erase element at index{}", index);
		}

		void Execute() override
		{
			_value = std::move(_ctx.data[_index]);
			_ctx.data.erase(_ctx.data.begin() + _index);
		}

		void Undo() override
		{
			_ctx.data.insert(_ctx.data.begin() + _index, std::move(_value));
		}

		[[nodiscard]]
		std::string Description() const override
		{
			return _description;
		}
	};
}
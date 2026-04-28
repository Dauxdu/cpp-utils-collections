export module EraseCommand;

import std;
import ICommand;

export namespace cmd
{
	template <typename ContextT>
	class Erase final : public ICommand
	{
	private:
		Context<ContextT> &_ctx;
		std::size_t _index = 0;
		ContextT _value;

	public:
		Erase(Context<ContextT> &ctx, std::size_t index) : _ctx(ctx), _index(index)
		{
			if (index >= ctx.data.size())
			{
				throw std::out_of_range("cmd::Erase: index out of range");
			}
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
			return std::format("{} was erased by index {}", _value, _index);
		}
	};
}
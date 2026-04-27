export module EraseCommand;

import std;
import ICommand;

export namespace cmd
{
	template <typename ContextT, typename ValueT>
	class Erase final : public ICommand<ContextT>
	{
	private:
		std::size_t _index = 0;
		ValueT _value;

	public:
		Erase(std::size_t index)
			: _index(index) {}

		void Execute(Context<ContextT> &ctx) override
		{
			_value = std::move(ctx.data[_index]);
			ctx.data.erase(ctx.data.begin() + _index);
		}

		void Undo(Context<ContextT> &ctx) override
		{
			ctx.data.insert(ctx.data.begin() + _index, _value);
		}

		[[nodiscard]]
		std::string Description() const override
		{
			return std::format("Erase {} by index {}.", _value, _index);
		}
	};
}
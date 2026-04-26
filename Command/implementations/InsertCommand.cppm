export module InsertCommand;

import std;
import ICommand;

export namespace cmd
{
	template<typename ContextT, typename ValueT>
	class Insert final : public ICommand
	{
	private:
		std::size_t _index = 0;
		ValueT _value;

	public:
		Insert(std::size_t index, ValueT value)
			: _index(index), _value(value) {};

		void Execute(Context<ContextT>& ctx) override
		{
			ctx.data.insert(ctx.data.begin() + _index, _value);
		}

		void Undo(Context<ContextT>& ctx) override
		{
			ctx.data.erase(ctx.data.begin() + _index);
		}

		[[nodiscard]]
		std::string Description() const override
		{
			return std::format("Insert {} by index {}.", _value, _index);
		}
	};
}
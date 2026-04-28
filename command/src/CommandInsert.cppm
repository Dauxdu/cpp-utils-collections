export module InsertCommand;

import std;
import ICommand;

export namespace cmd
{
	template <typename ContextT>
	class Insert final : public ICommand
	{
	private:
		Context<ContextT> &_ctx;
		std::size_t _index = 0;
		ContextT _value;
		std::string _description;

	public:
		Insert(Context<ContextT> &ctx, std::size_t index, ContextT value) 
			: _ctx(ctx), _index(index), _value(std::move(value))
		{
			if (index >= ctx.data.size())
			{
				throw std::out_of_range("cmd::Insert: index out of range");
			}
			_description = std::format("Insert element {} at index {} by ", value, index);
		};

		void Execute() override
		{
			_ctx.data.insert(_ctx.data.begin() + _index, _value);
		}

		void Undo() override
		{
			_ctx.data.erase(_ctx.data.begin() + _index);
		}

		[[nodiscard]]
		std::string Description() const override
		{
			return _description;
		}
	};
}
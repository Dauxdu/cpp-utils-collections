export module CommandUpdate;

import std;
import ICommand;

export namespace cmd
{
	template <typename ContextT>
	class Update final : public ICommand
	{
	private:
		<Context<ContextT>>& _cmd;
		std::size_t _index;
		ContextT _value;
		std::string _description;

	public:
		Update(Context<ContextT>& cmd, std::size_t index, ContextT value)
			: _cmd(cmd), _index(index), _value(std::move(value))
		{
			if (_index >= _cmd.get().data.size())
			{
				throw std::out_of_range("cmd::Update: index out of range");
			}
			_description = std::format("Update element {} at index {}", value, index);
		}

		void Execute() override
		{
			std::swap(_cmd.data[_index], _value);
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
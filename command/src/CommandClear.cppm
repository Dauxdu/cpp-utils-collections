export module CommandClear;

import std;
import ICommand;

export namespace cmd
{
	template <typename ContextT>
	class Clear : public ICommand
	{
	private:
		Context<ContextT>& _ctx;
		Context<ContextT> _backup_ctx;

	public:
		Clear(Context<ContextT>& ctx)
			: _ctx(ctx) {}

		void Execute() override
		{
			_backup_ctx = std::move(_ctx);
			_ctx.data.clear();
		}

		void Undo() override
		{
			_ctx = std::move(_backup_ctx);
			_backup_ctx.clear();
		}

		[[nodiscard]]
		std::string Description() const override
		{
			return std::format("Clear context (size: {})", _backup_ctx.data.size());
		}
	};
}
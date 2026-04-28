export module CommandClear;

import std;
import ICommand;

export namespace cmd
{
	template <typename ContextT>
	class Clear final : public ICommand
	{
	private:
		Context<ContextT>& _ctx;
		Context<ContextT> _backup_ctx;
		std::string _description;

	public:
		Clear(Context<ContextT>& ctx)
			: _ctx(ctx), _description(std::format("Clear data (size: {})", ctx.data.size())) {}

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
			return _description;
		}
	};
}
export module CommandHistory;

import std;
import ICommand;

export namespace cmd
{
    class CommandHistory
    {
    private:
        std::size_t _max_history = 0;
        std::deque<std::unique_ptr<ICommand>> _undo_cmds;
        std::deque<std::unique_ptr<ICommand>> _redo_cmds;

        void Trim() noexcept
        {
            if (_undo_cmds.size() > _max_history)
            {
                _undo_cmds.pop_front();
            }
        }

    public:
        explicit CommandHistory(std::size_t max_history = 50) : _max_history{std::max(max_history, std::size_t{1})} {}

        [[nodiscard]]
        std::size_t Size() const noexcept
        {
            return _undo_cmds.size();
        }

        [[nodiscard]]
        bool Empty() const noexcept
        {
            return _undo_cmds.empty();
        }

        [[nodiscard]]
        bool CanUndo() const noexcept
        {
            return !_undo_cmds.empty();
        }

        [[nodiscard]]
        bool CanRedo() const noexcept
        {
            return !_redo_cmds.empty();
        }

        void Clear() noexcept
        {
            _undo_cmds.clear();
            _redo_cmds.clear();
        }

        [[nodiscard]]
        std::vector<std::string> UndoDescriptions() const
        {
            std::vector<std::string> descs;
            for (const auto &cmd : _undo_cmds)
            {
                descs.push_back(cmd->Description());
            }
            return descs;
        }

        [[nodiscard]]
        std::vector<std::string> RedoDescriptions() const
        {
            std::vector<std::string> descs;
            for (const auto &cmd : _redo_cmds)
            {
                descs.push_back(cmd->Description());
            }
            return descs;
        }

        void Execute(std::unique_ptr<ICommand> cmd)
        {
            if (!cmd)
            {
                throw std::invalid_argument("cmd::History: not a command.");
            }

            cmd->Execute();
            _redo_cmds.clear();
            _undo_cmds.push_back(std::move(cmd));
            Trim();
        }

        void Undo(std::size_t steps = 1)
        {
            steps = std::min(steps, _undo_cmds.size());
            while (steps-- > 0)
            {
                auto &cmd = _undo_cmds.back();
                cmd->Undo();
                _redo_cmds.push_back(std::move(cmd));
                _undo_cmds.pop_back();
            }
        }

        void Redo(std::size_t steps = 1)
        {
            steps = std::min(steps, _redo_cmds.size());
            while (steps-- > 0)
            {
                auto &cmd = _redo_cmds.back();
                cmd->Execute();
                _undo_cmds.push_back(std::move(cmd));
                _redo_cmds.pop_back();
            }
            Trim();
        }
    };
}
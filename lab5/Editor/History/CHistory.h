#pragma once

#include "../Command/ICommand.h"
#include "../Document/IHistory.h"
#include <vector>

class CHistory final : public IHistory
{
public:
	[[nodiscard]] bool CanUndo() const override;
	void Undo() override;

	[[nodiscard]] bool CanRedo() const override;
	void Redo() override;

	void AddAndExecuteCommand(ICommandPtr&& command) override;

private:
	std::vector<ICommandPtr> m_commands;
	std::size_t m_currentCommandIndex = 0;
};

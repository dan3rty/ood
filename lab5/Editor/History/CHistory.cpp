#include "CHistory.h"

bool CHistory::CanUndo() const
{
	return m_currentCommandIndex > 0;
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_commands[--m_currentCommandIndex]->Rollback();
	}
}

bool CHistory::CanRedo() const
{
	return m_currentCommandIndex < m_commands.size();
}

void CHistory::Redo()
{
	if (CanRedo())
	{
		m_commands[m_currentCommandIndex++]->Execute();
	}
}

void CHistory::AddAndExecuteCommand(ICommandPtr&& command)
{
	command->Execute();

	m_commands.erase(m_commands.begin() + static_cast<int>(m_currentCommandIndex), m_commands.end());
	m_commands.push_back(std::move(command));
	++m_currentCommandIndex;
}

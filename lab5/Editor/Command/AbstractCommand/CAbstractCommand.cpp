#include "CAbstractCommand.h"

void CAbstractCommand::Execute()
{
	if (!m_isExecuted)
	{
		DoExecute();
		m_isExecuted = true;
	}
}

void CAbstractCommand::Rollback()
{
	if (m_isExecuted)
	{
		DoRollback();
		m_isExecuted = false;
	}
}

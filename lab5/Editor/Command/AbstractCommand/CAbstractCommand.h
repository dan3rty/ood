#pragma once

#include "../ICommand.h"

class CAbstractCommand : public ICommand
{
public:
	void Execute() final;
	void Rollback() final;

protected:
	virtual void DoExecute() = 0;
	virtual void DoRollback() = 0;

private:
	bool m_isExecuted = false;
};

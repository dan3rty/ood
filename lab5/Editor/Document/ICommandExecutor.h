#pragma once

#include "../Command/ICommand.h"

class ICommandExecutor
{
public:
	virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;

	virtual ~ICommandExecutor() = default;
};

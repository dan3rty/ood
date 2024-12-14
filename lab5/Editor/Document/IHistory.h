#pragma once

#include "../Command/ICommand.h"
#include "ICommandExecutor.h"

// перераспределить файлы по папкам так, чтобы класс истории можно было юзать не ток в Document
// Поместить классы в namespace с названием папок
class IHistory : public ICommandExecutor
{
public:
	[[nodiscard]] virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;

	[[nodiscard]] virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;
};

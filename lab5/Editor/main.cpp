#include "Editor/CEditor.h"
#include "History/CHistory.h"
#include "Saver/CHtmlSaver.h"

int main()
{
	CHistory history;
	CHtmlSaver saver;
	CEditor editor(std::cin, std::cout, history, saver);
	editor.Start();

	return EXIT_SUCCESS;
}

#include "ArgumentParser/CArgumentParser.h"
#include "Transformer/CTransformer.h"
#include <iostream>

int main(const int argc, char const** argv)
{
	try
	{
		const CArgumentParser parser(argc, argv);
		auto const args = parser.Parse();

		const CTransformer transformer(args);
		transformer.Transform();
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
// декоратор должен делегировать внутреннему объекту вызовы всех своих объектов
// программа не работает (сама себя фигово компресснул и закодировал)
// при компрессии необходимо учитывать все даннеы а не только те, что поданы в блок
// можно доработать алгритм компрессии с учётом битовых приколов
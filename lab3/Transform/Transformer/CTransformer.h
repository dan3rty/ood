#pragma once

#include "../ArgumentParser/CArgumentParser.h"
#include "../InputDataStream/IInputDataStream.h"
#include "../OutputDataStream/IOutputDataStream.h"
#include <memory>

class CTransformer
{
public:
	explicit CTransformer(Args const& args);

	void Transform() const;

private:
	void AddDecorators(Args const& args);

	IInputDataStreamPtr m_input;
	IOutputDataStreamPtr m_output;
};

template <typename Decorator, typename... Args>
auto MakeDecorator(Args const&... args)
{
	return [=](auto&& b) {
		return std::make_unique<Decorator>(std::forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator<<(Component&& component, Decorator const& decorate)
{
	return decorate(std::forward<Component>(component));
}

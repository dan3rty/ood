#pragma once

#include "../../../Styles/IStyle.h"
#include "../CGroupStyleImpl.h"
#include <functional>

using StyleCallback = std::function<void(IStyle&)>;
using StyleEnumerator = std::function<void(StyleCallback const&)>;

using CGroupFillStyle = CGroupStyleImpl<IStyle, StyleEnumerator>;

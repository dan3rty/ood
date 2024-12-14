#define CATCH_CONFIG_MAIN
#include "../App/Adapter/CModernGraphicsRendererCanvasAdapter.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("modern graphics to canvas adapter")
{
	GIVEN("a modern graphics renderer")
	{
		std::ostringstream output;
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);

		AND_GIVEN("an adapter to canvas")
		{
			renderer.BeginDraw();
			app::CModernGraphicsRendererCanvasAdapter adapter(renderer);

			WHEN("moving the cursor")
			{
				adapter.MoveTo(20, 50);

				THEN("nothing happens with the output")
				{
					REQUIRE(output.str() == "<draw>\n");
				}

				AND_WHEN("drawing a line")
				{
					adapter.LineTo(30, 12);

					THEN("it starts from the initial point with default color")
					{
						std::string const expected = R"(<draw>
  <line fromX="20" fromY="50" toX="30" toY="12">
    <color r="0.0" g="0.0" b="0.0" a="1.00"/>
  </line>
)";
						REQUIRE(output.str() == expected);
					}

					AND_WHEN("drawing another line")
					{
						adapter.LineTo(45, 6);

						THEN("it starts from the previous end")
						{
							std::string const expected = R"(<draw>
  <line fromX="20" fromY="50" toX="30" toY="12">
    <color r="0.0" g="0.0" b="0.0" a="1.00"/>
  </line>
  <line fromX="30" fromY="12" toX="45" toY="6">
    <color r="0.0" g="0.0" b="0.0" a="1.00"/>
  </line>
)";
							REQUIRE(output.str() == expected);
						}
					}
				}

				AND_WHEN("setting the color")
				{
					adapter.SetColor(0xFF0080);

					AND_WHEN("drawing a line")
					{
						adapter.LineTo(30, 12);

						THEN("it has that color")
						{
							std::string const expected = R"(<draw>
  <line fromX="20" fromY="50" toX="30" toY="12">
    <color r="1.0" g="0.0" b="0.5" a="1.00"/>
  </line>
)";
							REQUIRE(output.str() == expected);
						}
					}
				}
			}

			WHEN("drawing the line from scratch")
			{
				adapter.LineTo(12, 13);

				THEN("it starts from 0, 0")
				{
					std::string const expected = R"(<draw>
  <line fromX="0" fromY="0" toX="12" toY="13">
    <color r="0.0" g="0.0" b="0.0" a="1.00"/>
  </line>
)";
					REQUIRE(output.str() == expected);
				}
			}
		}
	}
}

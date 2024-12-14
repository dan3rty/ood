#define CATCH_CONFIG_MAIN
#include "../App/Adapter/CModernGraphicsRendererCanvasAdapter.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("modern graphics to canvas adapter")
{
	GIVEN("an adapter to canvas")
	{
		std::ostringstream output;
		app::CModernGraphicsRendererCanvasAdapter adapter(output);

		WHEN("moving the cursor")
		{
			adapter.MoveTo(20, 50);

			THEN("nothing happens with the output")
			{
				REQUIRE(output.str() == "<draw>\n");
			}

			AND_WHEN("drawing the line")
			{
				adapter.LineTo(30, 12);

				THEN("it starts from the initial point")
				{
					std::string const expected = R"(<draw>
  <line fromX="20" fromY="50" toX="30" toY="12"/>
)";
					REQUIRE(output.str() == expected);
				}

				AND_WHEN("drawing another line")
				{
					adapter.LineTo(45, 6);

					THEN("it starts from the previous end")
					{
						std::string const expected = R"(<draw>
  <line fromX="20" fromY="50" toX="30" toY="12"/>
  <line fromX="30" fromY="12" toX="45" toY="6"/>
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
  <line fromX="0" fromY="0" toX="12" toY="13"/>
)";
				REQUIRE(output.str() == expected);
			}
		}
	}
}

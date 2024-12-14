#define CATCH_CONFIG_MAIN
#include "../Canvas/CCanvas.h"
#include "../Designer/CDesigner.h"
#include "../Shapes/Ellipse/CEllipse.h"
#include "../Shapes/Rectangle/CRectangle.h"
#include "../Shapes/RegularPolygon/CRegularPolygon.h"
#include "../Shapes/Triangle/CTriangle.h"
#include "catch.hpp"
#include "fakeit.hpp"

TEST_CASE("shapes")
{
	fakeit::Mock<ICanvas> canvasMock;
	fakeit::Fake(Method(canvasMock, SetColor));
	fakeit::Fake(Method(canvasMock, DrawLine));
	fakeit::Fake(Method(canvasMock, DrawEllipse));

	auto& canvas = canvasMock.get();

	SECTION("ellipse")
	{
		GIVEN("color, center point, vertical and horizontal radius")
		{
			auto const color = Color::Red;
			Point const center = { 100, 200 };
			int const hRadius = 20;
			int const vRadius = 30;

			WHEN("creating an ellipse")
			{
				CEllipse ellipse(color, center, hRadius, vRadius);

				THEN("it has correct parameters")
				{
					REQUIRE(ellipse.GetColor() == color);

					REQUIRE(ellipse.GetCenter() == center);

					REQUIRE(ellipse.GetHorizontalRadius() == hRadius);
					REQUIRE(ellipse.GetVerticalRadius() == vRadius);
				}

				AND_WHEN("drawing the ellipse")
				{
					ellipse.Draw(canvas);

					THEN("it is drawn correctly")
					{
						fakeit::Verify(Method(canvasMock, SetColor).Using(color));
						fakeit::Verify(Method(canvasMock, DrawEllipse).Using(center, hRadius, vRadius));
					}
				}
			}
		}
	}

	SECTION("rectangle")
	{
		GIVEN("color, left top corner, right bottom corner")
		{
			auto const color = Color::Red;
			Point const leftTop = { 100, 200 };
			Point const rightBottom = { 200, 400 };

			WHEN("creating a rectangle")
			{
				CRectangle rectangle(color, leftTop, rightBottom);

				THEN("it has correct parameters")
				{
					REQUIRE(rectangle.GetColor() == color);

					REQUIRE(rectangle.GetLeftTop() == leftTop);
					REQUIRE(rectangle.GetRightBottom() == rightBottom);
				}

				AND_WHEN("drawing the rectangle")
				{
					rectangle.Draw(canvas);

					THEN("it is drawn correctly")
					{
						fakeit::Verify(Method(canvasMock, SetColor).Using(color));
						fakeit::Verify(Method(canvasMock, DrawLine)).Exactly(4);
					}
				}
			}
		}

		GIVEN("color, left top corner, width and height")
		{
			auto const color = Color::Red;
			Point const leftTop = { 100, 200 };
			int const width = 100;
			int const height = 200;

			WHEN("creating a rectangle")
			{
				CRectangle rectangle(color, leftTop, width, height);

				THEN("it has correct parameters")
				{
					REQUIRE(rectangle.GetColor() == color);

					REQUIRE(rectangle.GetLeftTop() == leftTop);
					REQUIRE(rectangle.GetRightBottom() == Point{ leftTop.x + width, leftTop.y + height });
				}
			}
		}
	}

	SECTION("regular polygon")
	{
		GIVEN("color, vertex count, center point and radius")
		{
			auto const color = Color::Red;
			std::size_t const vertexCount = 3;
			Point const center = { 100, 200 };
			int const radius = 30;

			WHEN("creating a regular polygon")
			{
				CRegularPolygon polygon(color, vertexCount, center, radius);

				THEN("it has correct parameters")
				{
					REQUIRE(polygon.GetColor() == color);

					REQUIRE(polygon.GetVertexCount() == vertexCount);
					REQUIRE(polygon.GetCenter() == center);
					REQUIRE(polygon.GetRadius() == radius);
				}

				AND_WHEN("drawing the polygon")
				{
					polygon.Draw(canvas);

					THEN("it is drawn correctly")
					{
						fakeit::Verify(Method(canvasMock, SetColor).Using(color));
						fakeit::Verify(Method(canvasMock, DrawLine)).Exactly(vertexCount);
					}
				}
			}
		}

		GIVEN("invalid vertex count")
		{
			std::size_t const vertexCount = 1;

			WHEN("creating a regular polygon")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(CRegularPolygon(Color::Green, vertexCount, { 1, 1 }, 1), std::invalid_argument);
				}
			}
		}

		GIVEN("borderline invalid vertex count")
		{
			std::size_t const vertexCount = 2;

			WHEN("creating a regular polygon")
			{
				CRegularPolygon polygon(Color::Green, vertexCount, { 1, 1 }, 1);

				THEN("it is created all right and has the right vertex count")
				{
					REQUIRE(polygon.GetVertexCount() == vertexCount);
				}
			}
		}
	}

	SECTION("triangle")
	{
		GIVEN("color and 3 vertices")
		{
			auto const color = Color::Red;
			Point const vertex1 = { 100, 200 };
			Point const vertex2 = { 150, 250 };
			Point const vertex3 = { 100, 300 };

			WHEN("creating a triangle")
			{
				CTriangle triangle(color, vertex1, vertex2, vertex3);

				THEN("it has correct parameters")
				{
					REQUIRE(triangle.GetColor() == color);

					REQUIRE(triangle.GetVertex1() == vertex1);
					REQUIRE(triangle.GetVertex2() == vertex2);
					REQUIRE(triangle.GetVertex3() == vertex3);
				}

				AND_WHEN("drawing the triangle")
				{
					triangle.Draw(canvas);

					THEN("it is drawn correctly")
					{
						fakeit::Verify(Method(canvasMock, SetColor).Using(color));
						fakeit::Verify(Method(canvasMock, DrawLine)).Exactly(3);
					}
				}
			}
		}
	}
}

TEST_CASE("shape factory")
{
	GIVEN("a factory")
	{
		CShapeFactory factory;

		AND_GIVEN("valid ellipse description")
		{
			std::string const description = "ellipse pink 100 100 50 40";

			WHEN("creating a shape")
			{
				auto const shape = factory.CreateShape(description);

				THEN("it is a valid ellipse")
				{
					auto const* ellipse = dynamic_cast<CEllipse const*>(shape.get());

					REQUIRE(ellipse != nullptr);

					REQUIRE(ellipse->GetColor() == Color::Pink);

					REQUIRE(ellipse->GetCenter() == Point{ 100, 100 });
					REQUIRE(ellipse->GetHorizontalRadius() == 50);
					REQUIRE(ellipse->GetVerticalRadius() == 40);
				}
			}
		}

		AND_GIVEN("valid rectangle description")
		{
			std::string const description = "rectangle black 100 100 50 40";

			WHEN("creating a shape")
			{
				auto const shape = factory.CreateShape(description);

				THEN("it is a valid rectangle")
				{
					auto const* rectangle = dynamic_cast<CRectangle const*>(shape.get());

					REQUIRE(rectangle != nullptr);

					REQUIRE(rectangle->GetColor() == Color::Black);

					REQUIRE(rectangle->GetLeftTop() == Point{ 100, 100 });
					REQUIRE(rectangle->GetRightBottom() == Point{ 150, 140 });
				}
			}
		}

		AND_GIVEN("valid regular polygon description")
		{
			std::string const description = "regular-polygon yellow 4 100 100 50";

			WHEN("creating a shape")
			{
				auto const shape = factory.CreateShape(description);

				THEN("it is a valid regular polygon")
				{
					auto const* regularPolygon = dynamic_cast<CRegularPolygon const*>(shape.get());

					REQUIRE(regularPolygon != nullptr);

					REQUIRE(regularPolygon->GetColor() == Color::Yellow);

					REQUIRE(regularPolygon->GetVertexCount() == 4);
					REQUIRE(regularPolygon->GetCenter() == Point{ 100, 100 });
					REQUIRE(regularPolygon->GetRadius() == 50);
				}
			}
		}

		AND_GIVEN("valid triangle description")
		{
			std::string const description = "triangle green 100 200 150 250 100 300";

			WHEN("creating a shape")
			{
				auto const shape = factory.CreateShape(description);

				THEN("it is a valid triangle")
				{
					auto const* triangle = dynamic_cast<CTriangle const*>(shape.get());

					REQUIRE(triangle != nullptr);

					REQUIRE(triangle->GetColor() == Color::Green);

					REQUIRE(triangle->GetVertex1() == Point{ 100, 200 });
					REQUIRE(triangle->GetVertex2() == Point{ 150, 250 });
					REQUIRE(triangle->GetVertex3() == Point{ 100, 300 });
				}
			}
		}

		AND_GIVEN("empty description")
		{
			std::string const description;

			WHEN("trying to create a shape")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(factory.CreateShape(description), std::invalid_argument);
				}
			}
		}

		AND_GIVEN("description with invalid shape")
		{
			std::string const description = "my-ass red 100 100";

			WHEN("trying to create a shape")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(factory.CreateShape(description), std::invalid_argument);
				}
			}
		}

		AND_GIVEN("description with invalid arguments count")
		{
		}

		AND_GIVEN("description with invalid color")
		{
			std::string const description = "rectangle bloody 100 100 50 50";

			WHEN("trying to create a shape")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(factory.CreateShape(description), std::invalid_argument);
				}
			}
		}

		AND_GIVEN("description with invalid number")
		{
			std::string const description = "rectangle green 1s00 100 50 50";

			WHEN("trying to create a shape")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(factory.CreateShape(description), std::invalid_argument);
				}
			}
		}
	}
}

TEST_CASE("picture draft")
{
	GIVEN("a picture draft")
	{
		CPictureDraft draft;

		WHEN("it is just created")
		{
			THEN("it is empty")
			{
				REQUIRE(draft.IsEmpty());
			}
		}

		WHEN("adding a couple of shapes")
		{
			draft.AddShape(std::make_unique<CEllipse>(Color::Green, Point{ 100, 100 }, 30, 80));
			draft.AddShape(std::make_unique<CRectangle>(Color::Yellow, Point{ 100, 100 }, 60, 50));

			THEN("it is not empty")
			{
				REQUIRE_FALSE(draft.IsEmpty());
			}

			THEN("it contains exactly 2 shapes")
			{
				REQUIRE(draft.begin() + 2 == draft.end());
			}

			THEN("it contains shapes in the order of addition")
			{
				auto const& shape1 = *draft.begin();
				auto const* ellipse = dynamic_cast<CEllipse const*>(shape1.get());
				REQUIRE(ellipse != nullptr);
				REQUIRE(ellipse->GetColor() == Color::Green);
				REQUIRE(ellipse->GetCenter() == Point{ 100, 100 });
				REQUIRE(ellipse->GetHorizontalRadius() == 30);
				REQUIRE(ellipse->GetVerticalRadius() == 80);

				auto const& shape2 = *(draft.begin() + 1);
				auto const* rectangle = dynamic_cast<CRectangle const*>(shape2.get());
				REQUIRE(rectangle != nullptr);
				REQUIRE(rectangle->GetColor() == Color::Yellow);
				REQUIRE(rectangle->GetLeftTop() == Point{ 100, 100 });
				REQUIRE(rectangle->GetRightBottom() == Point{ 160, 150 });
			}
		}
	}
}

TEST_CASE("designer")
{
	fakeit::Mock<IShapeFactory> factoryMock;
	fakeit::When(Method(factoryMock, CreateShape)).AlwaysDo([](std::string const& /* description */) -> CShapePtr {
		return std::make_unique<CEllipse>(Color::Pink, Point{ 100, 100 }, 12, 13);
	});

	auto& factory = factoryMock.get();

	GIVEN("input and output streams")
	{
		std::istringstream input;
		std::ostringstream output;

		AND_GIVEN("a designer")
		{
			CDesigner designer(factory);

			WHEN("passing empty descriptions")
			{
				input.str("\n\n\n");
				auto const draft = designer.CreateDraft(input, output);

				THEN("no shapes are created")
				{
					fakeit::VerifyNoOtherInvocations(factoryMock);
				}

				THEN("draft is empty")
				{
					REQUIRE(draft.IsEmpty());
				}
			}

			WHEN("passing comments")
			{
				input.str("# not a shape\n# like, totally, bro\n");
				auto const draft = designer.CreateDraft(input, output);

				THEN("no shapes are created")
				{
					fakeit::VerifyNoOtherInvocations(factoryMock);
				}

				THEN("draft is empty")
				{
					REQUIRE(draft.IsEmpty());
				}
			}

			WHEN("passing a couple of valid descriptions")
			{
				input.str("rectangle whatever\nWe can do the tango just for two\n");
				auto const draft = designer.CreateDraft(input, output);

				THEN("two shapes are created")
				{
					fakeit::Verify(Method(factoryMock, CreateShape)).Exactly(2);
				}

				THEN("draft is populated with mock shapes")
				{
					REQUIRE_FALSE(draft.IsEmpty());
					REQUIRE(draft.begin() + 2 == draft.end());
				}
			}

			WHEN("shape creation throws an exception")
			{
				fakeit::When(Method(factoryMock, CreateShape)).AlwaysThrow(std::invalid_argument("oops"));
				input.str("If I could only reach you\n");
				auto const draft = designer.CreateDraft(input, output);

				THEN("error message is written in the output")
				{
					REQUIRE(output.str() == "Error: oops\n  Skipping 'If I could only reach you' shape\n");
				}

				THEN("draft is empty")
				{
					REQUIRE(draft.IsEmpty());
				}
			}
		}
	}
}

TEST_CASE("canvas")
{
	GIVEN("output stream")
	{
		std::ostringstream output;

		WHEN("drawing nothing")
		{
			{
				CCanvas canvas(output);
			}

			THEN("output contains empty SVG")
			{
				REQUIRE(output.str() == "<svg viewBox=\"0 0 800 600\" xmlns=\"http://www.w3.org/2000/svg\">\n</svg>\n");
			}
		}

		WHEN("drawing a line with color")
		{
			{
				CCanvas canvas(output);
				canvas.SetColor(Color::Pink);
				canvas.DrawLine({ 100, 100 }, { 200, 200 });
			}

			THEN("output contains SVG with that line")
			{
				REQUIRE(output.str() == "<svg viewBox=\"0 0 800 600\" xmlns=\"http://www.w3.org/2000/svg\">\n"
										"  <line x1=\"100\" y1=\"100\" x2=\"200\" y2=\"200\" stroke=\"pink\" />\n"
										"</svg>\n");
			}
		}

		WHEN("drawing a circle with color")
		{
			{
				CCanvas canvas(output);
				canvas.SetColor(Color::Yellow);
				canvas.DrawEllipse({ 100, 100 }, 50, 40);
			}

			THEN("output contains SVG with that circle")
			{
				REQUIRE(output.str() == "<svg viewBox=\"0 0 800 600\" xmlns=\"http://www.w3.org/2000/svg\">\n"
										"  <ellipse cx=\"100\" cy=\"100\" rx=\"50\" ry=\"40\" stroke=\"yellow\" fill=\"none\" />\n"
										"</svg>\n");
			}
		}

		WHEN("drawing a shape without setting the color")
		{
			{
				CCanvas canvas(output);
				canvas.DrawLine({ 100, 100 }, { 200, 200 });
			}

			THEN("black is used as default")
			{
				REQUIRE(output.str() == "<svg viewBox=\"0 0 800 600\" xmlns=\"http://www.w3.org/2000/svg\">\n"
										"  <line x1=\"100\" y1=\"100\" x2=\"200\" y2=\"200\" stroke=\"black\" />\n"
										"</svg>\n");
			}
		}
	}
}

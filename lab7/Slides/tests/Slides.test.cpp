#define CATCH_CONFIG_MAIN
#include "../ShapeGroup/CShapeGroup.h"
#include "../Shapes/Ellipse/CEllipse.h"
#include "../Shapes/Rectangle/CRectangle.h"
#include "catch.hpp"
#include "fakeit.hpp"

TEST_CASE("shape group")
{
	fakeit::Mock<ICanvas> canvasMock;
	fakeit::Fake(Method(canvasMock, DrawLine));
	fakeit::Fake(Method(canvasMock, DrawPolygon));
	fakeit::Fake(Method(canvasMock, DrawEllipse));

	auto& canvas = canvasMock.get();

	GIVEN("a group")
	{
		CShapeGroup group;

		WHEN("it is just created")
		{
			THEN("it is empty")
			{
				REQUIRE(group.GetShapesCount() == 0);
			}

			THEN("trying to get or remove shapes throws an exception")
			{
				REQUIRE_THROWS_AS(group.GetShapeAtIndex(0), std::out_of_range);
				REQUIRE_THROWS_AS(group.RemoveShapeAtIndex(0), std::out_of_range);
			}

			THEN("the frame is null")
			{
				REQUIRE_FALSE(group.GetFrame().has_value());
			}

			THEN("fill style is null and has no color")
			{
				auto const fillStyle = group.GetFillStyle();

				REQUIRE_FALSE(fillStyle->IsEnabled().has_value());
				REQUIRE_FALSE(fillStyle->GetColor().has_value());
			}

			THEN("outline style is null and has no color nor thickness")
			{
				auto const outlineStyle = group.GetOutlineStyle();

				REQUIRE_FALSE(outlineStyle->IsEnabled().has_value());
				REQUIRE_FALSE(outlineStyle->GetColor().has_value());
				REQUIRE_FALSE(outlineStyle->GetThickness().has_value());
			}

			AND_WHEN("trying to draw it")
			{
				group.Draw(canvas);

				THEN("nothing is drawn")
				{
					fakeit::VerifyNoOtherInvocations(canvasMock);
				}
			}
		}

		WHEN("adding a shape in the end")
		{
			auto shape1 = std::make_shared<CRectangle>(PointD{ 100, 100 }, 50, 30);
			group.InsertShape(shape1, 0);

			THEN("group contains new shape")
			{
				REQUIRE(group.GetShapesCount() == 1);
				REQUIRE(group.GetShapeAtIndex(0)->GetFrame() == shape1->GetFrame());
			}

			THEN("group frame equals shape frame")
			{
				REQUIRE(group.GetFrame() == shape1->GetFrame());
			}

			THEN("fill and outline properties match")
			{
				REQUIRE(group.GetFillStyle()->GetColor() == shape1->GetFillStyle()->GetColor());
				REQUIRE(group.GetOutlineStyle()->GetColor() == shape1->GetOutlineStyle()->GetColor());
				REQUIRE(group.GetOutlineStyle()->GetThickness() == shape1->GetOutlineStyle()->GetThickness());
			}

			AND_WHEN("changing group frame")
			{
				group.SetFrame({ { 0, 0 }, 100, 60 });

				THEN("shape frame is moved and scaled accordingly")
				{
					REQUIRE(shape1->GetFrame() == RectD{ { 0, 0 }, 100, 60 });
				}
			}

			AND_WHEN("trying to get shape out of range")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(group.GetShapeAtIndex(1), std::out_of_range);
				}
			}

			AND_WHEN("trying to remove shape out of range")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(group.RemoveShapeAtIndex(1), std::out_of_range);
				}
			}

			AND_WHEN("drawing the frame")
			{
				canvasMock.ClearInvocationHistory();
				group.Draw(canvas);

				THEN("that single shape is drawn")
				{
					fakeit::Verify(Method(canvasMock, DrawPolygon)).Once();
				}
			}

			AND_WHEN("adding another shape in the beginning")
			{
				auto shape2 = std::make_shared<CEllipse>(PointD{ 100, 100 }, 50, 30);
				group.InsertShape(shape2, 0);

				THEN("it is placed before previous shape")
				{
					REQUIRE(group.GetShapesCount() == 2);
					REQUIRE(group.GetShapeAtIndex(0)->GetFrame() == shape2->GetFrame());
				}

				THEN("group frame is combined from shape frames")
				{
					REQUIRE(group.GetFrame() == RectD{ { 50, 70 }, 100, 60 });
				}

				THEN("fill and outline properties match as long as shape ones match")
				{
					REQUIRE(group.GetFillStyle()->GetColor() == shape2->GetFillStyle()->GetColor());
					REQUIRE(group.GetOutlineStyle()->GetColor() == shape2->GetOutlineStyle()->GetColor());
					REQUIRE(group.GetOutlineStyle()->GetThickness() == shape2->GetOutlineStyle()->GetThickness());
				}

				AND_WHEN("changing fill color in one of the shapes")
				{
					shape1->GetFillStyle()->SetColor(0x0000FF);

					THEN("group fill color becomes null")
					{
						REQUIRE_FALSE(group.GetFillStyle()->GetColor().has_value());
					}
				}

				AND_WHEN("disabling one of the shapes' style")
				{
					shape1->GetOutlineStyle()->Disable();

					THEN("group style status becomes null")
					{
						REQUIRE_FALSE(group.GetOutlineStyle()->IsEnabled().has_value());
					}
				}

				AND_WHEN("changing group frame")
				{
					group.SetFrame({ { 0, 0 }, 100, 60 });

					THEN("shape frame is moved and scaled accordingly")
					{
						REQUIRE(shape2->GetFrame() == RectD{ { 0, 0 }, 100, 60 });
					}
				}

				AND_WHEN("changing fill color for one of the shapes")
				{
					shape1->GetFillStyle()->SetColor(0xFF0000);

					THEN("groups color becomes null")
					{
						REQUIRE_FALSE(group.GetFillStyle()->GetColor().has_value());
					}
				}

				AND_WHEN("removing previous shape")
				{
					group.RemoveShapeAtIndex(1);

					THEN("only last shape is left")
					{
						REQUIRE(group.GetShapesCount() == 1);
						REQUIRE(group.GetShapeAtIndex(0)->GetFrame() == shape2->GetFrame());
					}
				}

				AND_WHEN("drawing the frame")
				{
					canvasMock.ClearInvocationHistory();
					group.Draw(canvas);

					THEN("both shapes are drawn")
					{
						fakeit::Verify(Method(canvasMock, DrawPolygon)).Once();
						fakeit::Verify(Method(canvasMock, DrawEllipse)).Once();
					}
				}
			}

			AND_WHEN("adding an empty group at the end")
			{
				auto childGroup = std::make_shared<CShapeGroup>();
				group.InsertShape(childGroup, 1);

				THEN("frame becomes null")
				{
					REQUIRE_FALSE(group.GetFrame().has_value());
				}
			}
		}
	}
}

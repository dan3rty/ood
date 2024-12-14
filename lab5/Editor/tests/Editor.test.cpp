#define CATCH_CONFIG_MAIN
#include "../Command/ChangeDocumentTitleCommand/CChangeDocumentTitleCommand.h"
#include "../Command/DeleteItemCommand/CDeleteItemCommand.h"
#include "../Command/InsertDocumentItemCommand/CInsertDocumentItemCommand.h"
#include "../Command/ResizeImageCommand/CResizeImageCommand.h"
#include "../Command/SetParagraphTextCommand/CSetParagraphTextCommand.h"
#include "../Document/CDocument.h"
#include "../History/CHistory.h"
#include "../Image/CImage.h"
#include "../Paragraph/CParagraph.h"
#include "../Saver/CHtmlSaver.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <filesystem>

TEST_CASE("document model")
{
	fakeit::Mock<IHistory> historyMock;
	fakeit::Fake(Method(historyMock, CanUndo));
	fakeit::Fake(Method(historyMock, Undo));
	fakeit::Fake(Method(historyMock, CanRedo));
	fakeit::Fake(Method(historyMock, Redo));
	fakeit::Fake(Method(historyMock, AddAndExecuteCommand));

	fakeit::Mock<ISaver> saverMock;
	fakeit::Fake(Method(saverMock, Save));

	auto& history = historyMock.get();
	auto& saver = saverMock.get();

	SECTION("document")
	{
		GIVEN("a document")
		{
			CDocument document(history, saver);

			WHEN("it is just created")
			{
				THEN("it has empty title")
				{
					REQUIRE(document.GetTitle().empty());
				}

				THEN("it has no items")
				{
					REQUIRE(document.GetItemsCount() == 0);
				}
			}

			WHEN("inserting a paragraph")
			{
				document.InsertParagraph("whatever", std::nullopt);

				THEN("it delegates to history")
				{
					fakeit::Verify(Method(historyMock, AddAndExecuteCommand)).Exactly(1);
				}
			}

			WHEN("inserting an image")
			{
				document.InsertImage("image.jpg", 50, 50, std::nullopt);

				THEN("it delegates to history")
				{
					fakeit::Verify(Method(historyMock, AddAndExecuteCommand)).Exactly(1);
				}
			}

			WHEN("changing the title")
			{
				document.SetTitle("whatever");

				THEN("it delegates to history")
				{
					fakeit::Verify(Method(historyMock, AddAndExecuteCommand)).Exactly(1);
				}
			}

			WHEN("operating with history")
			{
				document.CanUndo();
				document.Undo();
				document.CanRedo();
				document.Redo();

				THEN("it delegates to history")
				{
					fakeit::Verify(Method(historyMock, CanUndo)).Exactly(1);
					fakeit::Verify(Method(historyMock, Undo)).Exactly(1);
					fakeit::Verify(Method(historyMock, CanRedo)).Exactly(1);
					fakeit::Verify(Method(historyMock, Redo)).Exactly(1);
				}
			}

			WHEN("saving the document")
			{
				document.Save("whatever");

				THEN("it delegates to saver")
				{
					fakeit::Verify(Method(saverMock, Save)).Exactly(1);
				}
			}
		}
	}

	SECTION("image")
	{
		std::string const path = "image.jpg";

		WHEN("trying to create with invalid dimensions")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(CImage(path, 0, 10, history), std::invalid_argument);
				REQUIRE_THROWS_AS(CImage(path, 10, 0, history), std::invalid_argument);

				REQUIRE_THROWS_AS(CImage(path, 5001, 10, history), std::invalid_argument);
				REQUIRE_THROWS_AS(CImage(path, 10, 5001, history), std::invalid_argument);
			}
		}

		WHEN("trying to create with borderline dimensions")
		{
			THEN("it is created just fine")
			{
				REQUIRE_NOTHROW(CImage(path, 1, 10, history));
				REQUIRE_NOTHROW(CImage(path, 10, 1, history));

				REQUIRE_NOTHROW(CImage(path, 5000, 10, history));
				REQUIRE_NOTHROW(CImage(path, 10, 5000, history));
			}
		}

		WHEN("trying to create with invalid file extension")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(CImage("test.txt", 10, 10, history), std::invalid_argument);
			}
		}

		WHEN("trying to create with absent file")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(CImage("non_existing.jpg", 10, 10, history), std::runtime_error);
			}
		}

		WHEN("creating with valid parameters")
		{
			std::string tmpPath;

			{
				std::size_t const width = 50;
				std::size_t const height = 90;
				CImage image(path, width, height, history);
				tmpPath = image.GetPath();

				THEN("parameters match")
				{
					REQUIRE(image.GetWidth() == width);
					REQUIRE(image.GetHeight() == height);
				}

				THEN("a temporary path and file is generated")
				{
					REQUIRE(tmpPath != path);
					REQUIRE(std::filesystem::exists(tmpPath));
				}

				WHEN("resizing the image")
				{
					image.Resize(10, 10);

					THEN("it delegates to history")
					{
						fakeit::Verify(Method(historyMock, AddAndExecuteCommand)).Exactly(1);
					}
				}
			}

			AND_WHEN("image is destroyed")
			{
				THEN("temporary file is deleted")
				{
					REQUIRE_FALSE(std::filesystem::exists(tmpPath));
				}
			}
		}
	}

	SECTION("paragraph")
	{
		WHEN("creating a paragraph")
		{
			std::string const text = "text";
			CParagraph paragraph(text, history);

			THEN("it has initial text")
			{
				REQUIRE(paragraph.GetText() == text);
			}

			AND_WHEN("changing the text")
			{
				paragraph.SetText("another text");

				THEN("it delegates to history")
				{
					fakeit::Verify(Method(historyMock, AddAndExecuteCommand)).Exactly(1);
				}
			}
		}
	}

	SECTION("document item")
	{
		std::string const value = "one flesh one bone one true religion";

		fakeit::Mock<IImage> imageMock;
		fakeit::When(Method(imageMock, GetPath)).AlwaysReturn(value);
		fakeit::Fake(Method(imageMock, GetWidth));
		fakeit::Fake(Method(imageMock, GetHeight));
		fakeit::Fake(Method(imageMock, Resize));

		fakeit::Mock<IParagraph> paragraphMock;
		fakeit::When(Method(paragraphMock, GetText)).AlwaysReturn(value);
		fakeit::Fake(Method(paragraphMock, SetText));

		auto& image = imageMock.get();
		std::shared_ptr<IImage> imagePtr(&image);

		auto& paragraph = paragraphMock.get();
		std::shared_ptr<IParagraph> paragraphPtr(&paragraph);

		WHEN("creating a document item with image")
		{
			CDocumentItem item(std::move(imagePtr));

			THEN("it has that image")
			{
				REQUIRE(item.GetImage() != nullptr);
				REQUIRE(item.GetImage()->GetPath() == value);
			}

			THEN("it has no paragraph")
			{
				REQUIRE(item.GetParagraph() == nullptr);
			}
		}

		WHEN("creating a document item with paragraph")
		{
			CDocumentItem item(std::move(paragraphPtr));

			THEN("it has that paragraph")
			{
				REQUIRE(item.GetParagraph() != nullptr);
				REQUIRE(item.GetParagraph()->GetText() == value);
			}

			THEN("it has no image")
			{
				REQUIRE(item.GetImage() == nullptr);
			}
		}
	}
}

TEST_CASE("commands")
{
	fakeit::Mock<IImage> imageMock;
	fakeit::Fake(Method(imageMock, GetPath));
	fakeit::Fake(Method(imageMock, GetWidth));
	fakeit::Fake(Method(imageMock, GetHeight));
	fakeit::Fake(Method(imageMock, Resize));

	fakeit::Mock<IParagraph> paragraphMock;
	fakeit::Fake(Method(paragraphMock, GetText));
	fakeit::Fake(Method(paragraphMock, SetText));

	auto& paragraph = paragraphMock.get();
	auto& image = imageMock.get();

	CDocumentItem mockItem1((std::shared_ptr<IParagraph>(&paragraph)));
	CDocumentItem mockItem2((std::shared_ptr<IImage>(&image)));

	SECTION("change document title")
	{
		std::string title = "pretty raw title";
		std::string const oldTitle = title;
		std::string const newTitle = "BREAK YOUR FUCKING FACE TONIGHT";

		GIVEN("a change document title command")
		{
			CChangeDocumentTitleCommand command(title, newTitle);

			WHEN("executing it")
			{
				command.Execute();

				THEN("title changes")
				{
					REQUIRE(title == newTitle);
				}

				AND_WHEN("rolling it back")
				{
					command.Rollback();

					THEN("title restores")
					{
						REQUIRE(title == oldTitle);
					}
				}
			}
		}
	}

	SECTION("delete item")
	{
		GIVEN("a vector of items")
		{
			std::vector<CDocumentItem> items{ mockItem1, mockItem2 };

			WHEN("trying to create command with invalid index")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(CDeleteItemCommand(items, items.size() + 1), std::invalid_argument);
					REQUIRE_THROWS_AS(CDeleteItemCommand(items, items.size()), std::invalid_argument);
				}
			}

			AND_GIVEN("a valid delete item command")
			{
				CDeleteItemCommand command(items, 0);

				WHEN("executing it")
				{
					command.Execute();

					THEN("the right item is deleted")
					{
						REQUIRE(items.size() == 1);
						REQUIRE(items.at(0).GetImage() != nullptr);
					}

					AND_WHEN("rolling it back")
					{
						command.Rollback();

						THEN("the item is restored")
						{
							REQUIRE(items.size() == 2);
							REQUIRE(items.at(0).GetParagraph() != nullptr);
							REQUIRE(items.at(1).GetImage() != nullptr);
						}
					}
				}
			}
		}
	}

	SECTION("insert document item")
	{
		GIVEN("a vector with one item")
		{
			std::vector<CDocumentItem> items{ mockItem1 };

			WHEN("trying to create command with invalid index")
			{
				THEN("it throws an exception")
				{
					auto newItemPtr = std::make_shared<CDocumentItem>(mockItem2);
					REQUIRE_THROWS_AS(CInsertDocumentItemCommand(items, std::move(newItemPtr), items.size() + 1), std::invalid_argument);
				}
			}

		}
	}

	SECTION("resize image")
	{
		GIVEN("a resize image command")
		{
			int width = 100;
			int height = 100;
			int const oldWidth = width;
			int const oldHeight = height;
			int const newWidth = 50;
			int const newHeight = 50;
			CResizeImageCommand command(width, height, newWidth, newHeight);

			WHEN("executing it")
			{
				command.Execute();

				THEN("values change")
				{
					REQUIRE(width == newWidth);
					REQUIRE(height == newHeight);
				}

				AND_WHEN("rolling it back")
				{
					command.Rollback();

					THEN("values restore")
					{
						REQUIRE(width == oldWidth);
						REQUIRE(height == oldHeight);
					}
				}
			}
		}
	}

	SECTION("set paragraph text")
	{
		std::string text = "pizza date on skype";
		std::string const oldText = text;
		std::string const newText = "I HOPE YOU KNOW I PACK A CHAINSAW";

		GIVEN("a set paragraph text command")
		{
			CSetParagraphTextCommand command(text, newText);

			WHEN("executing it")
			{
				command.Execute();

				THEN("text changes")
				{
					REQUIRE(text == newText);
				}

				AND_WHEN("rolling it back")
				{
					command.Rollback();

					THEN("text restores")
					{
						REQUIRE(text == oldText);
					}
				}
			}
		}
	}
}

TEST_CASE("history")
{
	fakeit::Mock<ICommand> mockCommand1;
	fakeit::Fake(Method(mockCommand1, Execute));
	fakeit::Fake(Method(mockCommand1, Rollback));
	fakeit::Mock<ICommand> mockCommand2;
	fakeit::Fake(Method(mockCommand2, Execute));
	fakeit::Fake(Method(mockCommand2, Rollback));

	auto& command1 = mockCommand1.get();
	auto& command2 = mockCommand2.get();

	GIVEN("a history")
	{
		CHistory history;

		WHEN("it is just created")
		{
			THEN("it can not undo nor redo")
			{
				REQUIRE_FALSE(history.CanUndo());
				REQUIRE_FALSE(history.CanRedo());
			}
		}

		WHEN("adding a command")
		{
			history.AddAndExecuteCommand(std::unique_ptr<ICommand>(&command1));

			THEN("command is executed")
			{
				fakeit::Verify(Method(mockCommand1, Execute)).Exactly(1);
			}

			THEN("history can undo")
			{
				REQUIRE(history.CanUndo());
			}

			THEN("history can not redo")
			{
				REQUIRE_FALSE(history.CanRedo());
			}

			AND_WHEN("undoing the command")
			{
				history.Undo();

				THEN("command is rolled back")
				{
					fakeit::Verify(Method(mockCommand1, Rollback)).Exactly(1);
				}

				THEN("history can not undo")
				{
					REQUIRE_FALSE(history.CanUndo());
				}

				THEN("history can redo")
				{
					REQUIRE(history.CanRedo());
				}

				AND_WHEN("redoing the command")
				{
					history.Redo();

					THEN("command is executed again")
					{
						fakeit::Verify(Method(mockCommand1, Execute)).Exactly(2);
					}

					THEN("history can undo")
					{
						REQUIRE(history.CanUndo());
					}

					THEN("history can not redo")
					{
						REQUIRE_FALSE(history.CanRedo());
					}
				}

				AND_WHEN("adding another command on top of that")
				{
					history.AddAndExecuteCommand(std::unique_ptr<ICommand>(&command2));

					THEN("history can undo")
					{
						REQUIRE(history.CanUndo());
					}

					THEN("history can not redo, because previous command is erased")
					{
						REQUIRE_FALSE(history.CanRedo());
					}
				}
			}
		}
	}
}

TEST_CASE("html saver")
{
	fakeit::Mock<IHistory> historyMock;
	fakeit::When(Method(historyMock, AddAndExecuteCommand)).AlwaysDo([](ICommandPtr const& command) {
		command->Execute();
	});

	auto& history = historyMock.get();

	GIVEN("a saver itself")
	{
		CHtmlSaver saver;

		AND_GIVEN("a document with a couple of elements")
		{
			CDocument document(history, saver);
			document.SetTitle("Test document");
			document.InsertParagraph("Fear 'me' you loathsome & lazy creatures", std::nullopt);
			document.InsertParagraph("I descend upon \"your\" <earth> from the skies", std::nullopt);
			document.InsertImage("image.jpg", 100, 80, std::nullopt);

			WHEN("saving the document")
			{
				auto const path = std::filesystem::temp_directory_path() / "output.html";
				auto const imagesPath = path.parent_path() / "html_images";
				document.Save(path.string());

				THEN("the document is saved correctly and text is properly escaped")
				{
					std::ifstream file(path.string());
					std::ostringstream buffer;
					buffer << file.rdbuf();
					file.close();

					std::string const result = buffer.str();
					std::string expected = R"(<html>
<head>
  <title>Test document</title>
</head>
<body>
  <p>Fear &apos;me&apos; you loathsome &amp; lazy creatures</p>
  <p>I descend upon &quot;your&quot; &lt;earth&gt; from the skies</p>
  <img src="path_here" width="100" height="80" />
</body>
</html>
)";

					expected.replace(expected.find("path_here"), 9, (imagesPath / "image_10.jpg").string());
					std::filesystem::remove(path);
					std::filesystem::remove_all(imagesPath);

					REQUIRE(result == expected);
				}
			}
		}
	}
}

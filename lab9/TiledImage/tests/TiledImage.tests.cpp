#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Tile.h"
#include "../Image.h"

class TestFixture {
public:
    TestFixture() {
        while (Tile::GetInstanceCount() > 0) {}
    }

    ~TestFixture() {
        REQUIRE(Tile::GetInstanceCount() == 0);
    }
};

TEST_CASE_METHOD(TestFixture, "CreateImageWithSingleColor") {
    Image img({16, 16}, '*');

    REQUIRE(img.GetSize().width == 16);
    REQUIRE(img.GetSize().height == 16);

    for (int y = 0; y < img.GetSize().height; ++y) {
        for (int x = 0; x < img.GetSize().width; ++x) {
            REQUIRE(img.GetPixel({x, y}) == '*');
        }
    }

    REQUIRE(Tile::GetInstanceCount() == 1);
}

TEST_CASE_METHOD(TestFixture, "SetAndGetPixel") {
    Image img({16, 16}, '.');
    REQUIRE(Tile::GetInstanceCount() == 1);

    img.SetPixel({0, 0}, '#');
    REQUIRE(img.GetPixel({0, 0}) == '#');
    REQUIRE(Tile::GetInstanceCount() == 2);

    img.SetPixel({10, 10}, '@');
    REQUIRE(img.GetPixel({10, 10}) == '@');
    REQUIRE(Tile::GetInstanceCount() == 3);

    img.SetPixel({15, 15}, 'X');
    REQUIRE(img.GetPixel({15, 15}) == 'X');
    REQUIRE(Tile::GetInstanceCount() == 3);
}

TEST_CASE_METHOD(TestFixture, "GetPixelOutOfBoundsImage") {
    Image img({16, 16}, '.');

    REQUIRE(img.GetPixel({-1, -1}) == 0xFFFFFF);
    REQUIRE(img.GetPixel({16, 16}) == 0xFFFFFF);
}

TEST_CASE_METHOD(TestFixture, "SetPixelOutOfBounds") {
    Image img({16, 16}, '.');

    img.SetPixel({-1, -1}, '#');
    REQUIRE(img.GetPixel({-1, -1}) == 0xFFFFFF);

    img.SetPixel({16, 16}, '#');
    REQUIRE(img.GetPixel({16, 16}) == 0xFFFFFF);
}

TEST_CASE_METHOD(TestFixture, "TileInstanceCount") {
    {
        Image img1({8, 8}, '*');
        REQUIRE(Tile::GetInstanceCount() == 1);

        Image img2({8, 8}, '#');
        REQUIRE(Tile::GetInstanceCount() == 2);

        img1.SetPixel({0, 0}, '@');
        REQUIRE(Tile::GetInstanceCount() == 3);
        REQUIRE(img1.GetPixel({0, 0}) == '@');
        REQUIRE(img2.GetPixel({0, 0}) != '@');

        img2.SetPixel({0, 0}, '&');
        REQUIRE(Tile::GetInstanceCount() == 4);
        REQUIRE(img2.GetPixel({0, 0}) == '&');
        REQUIRE(img1.GetPixel({0, 0}) != '&');
    }

    REQUIRE(Tile::GetInstanceCount() == 0);
}

TEST_CASE_METHOD(TestFixture, "DefaultConstructor") {
    Tile tile;
    for (int y = 0; y < Tile::SIZE; ++y) {
        for (int x = 0; x < Tile::SIZE; ++x) {
            REQUIRE(tile.GetPixel({x, y}) == 0xFFFFFF);
        }
    }
    REQUIRE(Tile::GetInstanceCount() == 1);
}

TEST_CASE_METHOD(TestFixture, "ParameterizedConstructor") {
    Tile tile('*');
    REQUIRE(Tile::GetInstanceCount() == 1);

    for (int y = 0; y < Tile::SIZE; ++y) {
        for (int x = 0; x < Tile::SIZE; ++x) {
            REQUIRE(tile.GetPixel({x, y}) == '*');
        }
    }
}

TEST_CASE_METHOD(TestFixture, "CopyConstructor") {
    Tile tile1('*');
    REQUIRE(Tile::GetInstanceCount() == 1);

    Tile tile2(tile1);
    REQUIRE(Tile::GetInstanceCount() == 2);

    for (int y = 0; y < Tile::SIZE; ++y) {
        for (int x = 0; x < Tile::SIZE; ++x) {
            REQUIRE(tile2.GetPixel({x, y}) == '*');
        }
    }
}

TEST_CASE_METHOD(TestFixture, "SetPixel") {
    Tile tile(0xFFFFFF);

    tile.SetPixel({0, 0}, '#');
    REQUIRE(tile.GetPixel({0, 0}) == '#');

    tile.SetPixel({7, 7}, '@');
    REQUIRE(tile.GetPixel({7, 7}) == '@');

    tile.SetPixel({8, 8}, 'X');
    REQUIRE(tile.GetPixel({8, 8}) == 0xFFFFFF);
}

TEST_CASE_METHOD(TestFixture, "GetPixelOutOfBoundsTile") {
    Tile tile('*');

    REQUIRE(tile.GetPixel({-1, -1}) == 0xFFFFFF);
    REQUIRE(tile.GetPixel({8, 8}) == 0xFFFFFF);
}

TEST_CASE_METHOD(TestFixture, "DestructorDecreasesInstanceCount") {
    {
        Tile tile;
        REQUIRE(Tile::GetInstanceCount() == 1);
    }
    REQUIRE(Tile::GetInstanceCount() == 0);
}

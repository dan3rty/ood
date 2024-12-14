add_executable(TiledImageTest
        TiledImage.tests.cpp
        ../CoW.h
        ../Drawer.h
        ../Drawer.cpp
        ../Geom.h
        ../Image.h
        ../Image.cpp
        ../ImageService.h
        ../ImageService.cpp
        ../Tile.h
)

target_link_libraries(TiledImageTest PUBLIC catch2 fakeit)
add_test(NAME TiledImageTest COMMAND TiledImageTest)

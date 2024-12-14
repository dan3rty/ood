add_executable(GraphicsClassAdapterTest
               GraphicsClassAdapter.test.cpp
               ../Libs/graphics_lib/ICanvas.h
               ../Libs/graphics_lib/Canvas/CCanvas.cpp
               ../Libs/graphics_lib/Canvas/CCanvas.h
               ../Libs/shape_drawing_lib/CanvasPainter/ICanvasDrawable.h
               ../Libs/shape_drawing_lib/Triangle/CTriangle.cpp
               ../Libs/shape_drawing_lib/Triangle/CTriangle.h
               ../Libs/shape_drawing_lib/Rectangle/CRectangle.cpp
               ../Libs/shape_drawing_lib/Rectangle/CRectangle.h
               ../Libs/shape_drawing_lib/CanvasPainter/CCanvasPainter.cpp
               ../Libs/shape_drawing_lib/CanvasPainter/CCanvasPainter.h
               ../Libs/modern_graphics_lib/ModernGraphicsRenderer/CModernGraphicsRenderer.cpp
               ../Libs/modern_graphics_lib/ModernGraphicsRenderer/CModernGraphicsRenderer.h
               ../Libs/modern_graphics_lib/Point/CPoint.cpp
               ../Libs/modern_graphics_lib/Point/CPoint.h
               ../App/PaintUtils.h
               ../App/PaintUtils.cpp
               ../App/Adapter/CModernGraphicsRendererCanvasAdapter.cpp
               ../App/Adapter/CModernGraphicsRendererCanvasAdapter.h)

target_link_libraries(GraphicsClassAdapterTest PUBLIC catch2)
add_test(NAME GraphicsClassAdapterTest COMMAND GraphicsClassAdapterTest)

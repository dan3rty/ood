add_executable(DesignerTest
        Designer.test.cpp
        ../Canvas/CCanvas.cpp
        ../Canvas/CCanvas.h
        ../PictureDraft/CPictureDraft.cpp
        ../PictureDraft/CPictureDraft.h
        ../Designer/IDesigner.h
        ../Designer/CDesigner.cpp
        ../Designer/CDesigner.h
        ../Painter/CPainter.cpp
        ../Painter/CPainter.h
        ../ShapeFactory/IShapeFactory.h
        ../ShapeFactory/CShapeFactory.cpp
        ../ShapeFactory/CShapeFactory.h
        ../Shapes/ShapeTypes.cpp
        ../Shapes/ShapeTypes.h
        ../Shapes/CShape.cpp
        ../Shapes/CShape.h
        ../Shapes/Ellipse/CEllipse.cpp
        ../Shapes/Ellipse/CEllipse.h
        ../Shapes/Rectangle/CRectangle.cpp
        ../Shapes/Rectangle/CRectangle.h
        ../Shapes/RegularPolygon/CRegularPolygon.cpp
        ../Shapes/RegularPolygon/CRegularPolygon.h
        ../Shapes/Triangle/CTriangle.cpp
        ../Shapes/Triangle/CTriangle.h)

target_link_libraries(DesignerTest PUBLIC catch2 fakeit)
add_test(NAME DesignerTest COMMAND DesignerTest)

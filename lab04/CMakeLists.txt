cmake_minimum_required(VERSION 3.14)
project(lab04)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(SOURCES
        main.cpp
        3dparty/jsmn.c
        commands/commands.cpp
        controller/controller.cpp
        exceptions/base_exception.cpp
        exceptions/container_exceptions.cpp
        exceptions/model_view_exceptions.cpp
        exceptions/scene_exceptions.cpp
        exceptions/upload_exceptions.cpp
        facade/facade.cpp
        gui/drawer.cpp
        gui/mainwindow.cpp
        managers/camera_manager.cpp
        managers/draw_manager.cpp
        managers/model_manager.cpp
        managers/upload_manager.cpp
        model_view/model_view.cpp
        objects/camera.cpp
        objects/composite_object.cpp
        objects/invisible_object.cpp
        objects/model.cpp
        objects/visible_object.cpp
        scene/scene.cpp
        transformations/command_interface.cpp
        transformations/dimensional_transformations.cpp
        transformations/model_transformations.cpp
        transformations/transformation_interface.cpp
        upload/uploader.cpp)

set(HEADERS
        3dparty/jsmn.h
        commands/commands.hpp
        containers/iterator/const_iterator.hpp
        containers/iterator/iterator.hpp
        containers/iterator/base_iterator.hpp
        containers/matrix/matrix.hpp
        containers/matrix/base_matrix.hpp
        containers/pair/pair.hpp
        containers/vector/vector.hpp
        containers/vector/base_vector.hpp
        controller/controller.hpp
        exceptions/base_exception.hpp
        exceptions/container_exceptions.hpp
        exceptions/model_view_exceptions.hpp
        exceptions/scene_exceptions.hpp
        exceptions/upload_exceptions.hpp
        facade/facade.hpp
        gui/drawer.hpp
        gui/mainwindow.hpp
        managers/camera_manager.hpp
        managers/draw_manager.hpp
        managers/model_manager.hpp
        managers/upload_manager.hpp
        model_view/model_view.hpp
        objects/camera.hpp
        objects/composite_object.hpp
        objects/invisible_object.hpp
        objects/model.hpp
        objects/scene_object.hpp
        objects/visible_object.hpp
        math3d/matrix4x4.hpp
        math3d/point3d.hpp
        math3d/vector4d.hpp
        scene/scene.hpp
        transformations/base_transformations.hpp
        transformations/command_interface.hpp
        transformations/dimensional_transformations.hpp
        transformations/model_transformations.hpp
        transformations/transformation_interface.hpp
        upload/base_uploader.hpp
        upload/uploader.hpp)

add_executable(lab04 ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
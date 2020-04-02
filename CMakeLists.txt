cmake_minimum_required(VERSION 3.1)

project(TestApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

SET(headers headers/projectroleenum.h headers/project.h headers/projectmodel.h headers/controller.h)
SET(sources src/controller.cpp src/projectmodel.cpp src/main.cpp)

add_executable(${PROJECT_NAME} ${headers} ${sources}     "qml.qrc")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Network)

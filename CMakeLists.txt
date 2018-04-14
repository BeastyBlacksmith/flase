
cmake_minimum_required( VERSION 3.7 )
project( sheepndogs )

set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Wall ")

set(sheepndogs_includes "src/" "src/common" "src/wnd" "src/libkdtree/kdtree++")
include_directories(${sheepndogs_includes})
file( MAKE_DIRECTORY "build/temp" )
file(GLOB sheepndogs_src1 "src/*.cpp")
file(GLOB_RECURSE sheepndogs_src2
        "src/common/*.cpp"
        "src/wnd/*.cpp"
        "src/Measure/*.cpp"
        "src/Motion/*.cpp"
        "src/Plotter/*.cpp"
        "src/Sheep/*.cpp"
        "src/Dogs/*.cpp"
        "src/Simulation/*.cpp"
        )

file(GLOB web_src "html/*.cpp")
file(GLOB sheep2web
        "src/common.cpp"
        "src/World.h"
        "src/World.cpp"
        "src/Motion/*.cpp"
        "src/Dogs/*.cpp"
        "src/Dogs/*.h"
        "src/Sheep/*.cpp"
        "src/Sheep/*.h"
        )

add_executable(sheepndogs ${sheepndogs_src1} ${sheepndogs_src2})
add_executable(flase_app ${web_src} ${sheep2web} html/util/ParameterField.cpp html/util/ParameterField.h)
find_package(Wt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GSL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${WT_INCLUDE_DIRS})

target_link_libraries(sheepndogs ${WT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES}
        GSL::gsl GSL::gslcblas m)
target_link_libraries(flase_app ${WT_LIBRARIES} GSL::gsl GSL::gslcblas m wt wthttp)

add_custom_target(cleantemp)
add_custom_command(TARGET cleantemp COMMAND rm -rf temp/*)

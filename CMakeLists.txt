
cmake_minimum_required( VERSION 2.8 )
project( sheepndogs )

set(CMAKE_CXX_FLAGS "-std=gnu++0x -O3 -Wall ")

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

add_executable(sheepndogs ${sheepndogs_src1} ${sheepndogs_src2})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(sheepndogs ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} gsl gslcblas m)

add_custom_target( cleantemp )
add_custom_command( TARGET cleantemp COMMAND rm -rf temp/*)

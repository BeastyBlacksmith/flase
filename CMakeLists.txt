
cmake_minimum_required( VERSION 2.8 )
project( sheepndogs )

set(CMAKE_CXX_FLAGS "-std=gnu++0x -O3 -Wall -L..")
#set( CMAKE_CXX_FLAGS "-O3 -fopenmp -pg -Wall" )
#set( CMAKE_CXX_FLAGS "-O0 -g -fopenmp -Wall" )

set( sheepndogs_includes "src/" "src/common" "src/wnd" "src/kdtree++" )
include_directories( ${sheepndogs_includes} "~/glew/include" "~/glut/include" )
file( MAKE_DIRECTORY "build/temp" )
file( GLOB_RECURSE sheepndogs_src "src/*.cpp" "src/common/*.cpp" "src/wnd/*.cpp" )
add_executable(sheepndogs ${sheepndogs_src} src/Measure.h src/Measure/Measure.cpp src/common/gl_includes.h)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(sheepndogs ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} gsl gslcblas m)


add_custom_target( cleantemp )
add_custom_command( TARGET cleantemp COMMAND rm -rf temp/*)

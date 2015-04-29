
cmake_minimum_required( VERSION 2.8 )
project( sheepndogs )

#set( CMAKE_CXX_FLAGS "-O3 -Wall" )
set( CMAKE_CXX_FLAGS "-std=gnu++0x -O3 -fopenmp -Wall" )
#set( CMAKE_CXX_FLAGS "-O3 -fopenmp -pg -Wall" )
#set( CMAKE_CXX_FLAGS "-O0 -g -fopenmp -Wall" )

set( sheepndogs_includes "src/" "src/common" "src/wnd" "src/kdtree++" )
include_directories( ${sheepndogs_includes} )
file( GLOB_RECURSE sheepndogs_src "src/*.cpp" "src/common/*.cpp" "src/wnd/*.cpp" )
file( MAKE_DIRECTORY "build/temp" )

add_executable( sheepndogs ${sheepndogs_src} )
target_link_libraries( sheepndogs m gsl gslcblas GL GLEW GLU glut )


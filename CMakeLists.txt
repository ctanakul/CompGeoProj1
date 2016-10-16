#Specify the version being used as well as language
cmake_minimum_required(VERSION 2.8)
#Name your project
project(Project1)
find_package( OpenCV REQUIRED )
add_executable( Bresenham bresenham.cpp )
target_link_libraries( Bresenham ${OpenCV_LIBS} )
cmake_minimum_required (VERSION 2.6)
project (TCPClient)
add_executable(TCPClient main.cpp class.cpp fonction.cpp) 
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(TCPClient ${OpenCV_LIBRARIES})
else(OpenCV_FOUND)
message(FATAL ERROR "Librarie OpenCV introuvable!")
endif(OpenCV_FOUND)



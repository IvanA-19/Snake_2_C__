cmake_minimum_required (VERSION 3.21)

project (New_folder)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable (New_folder main.cpp)

set(SFML_DIR "F:\\Cross-Zero_C++\\New folder\\lib\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(New_folder sfml-graphics sfml-audio)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)
# CMakeList.txt: проект CMake для AstMarker; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("AstMarker")

find_package(imgui CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (AstMarker "AstMarker.cpp" "AstMarker.h")
target_link_libraries(AstMarker PRIVATE imgui::imgui)
target_link_libraries(AstMarker PRIVATE unofficial::nativefiledialog::nfd)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AstMarker PROPERTY CXX_STANDARD 20)
endif()
# TODO: Добавьте тесты и целевые объекты, если это необходимо.

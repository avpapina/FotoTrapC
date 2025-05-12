# CMakeList.txt: проект CMake для FotoTrapC; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
# Добавьте источник в исполняемый файл этого проекта.
add_executable (FotoTrapC "camera.cpp")
set(OpenCV_DIR "C:/OpenCV/build/install/x64/vc17/lib") 

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FotoTrapC PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
find_package(OpenCV REQUIRED)
target_link_libraries(FotoTrapC ${OpenCV_LIBS})
 # Укажите ваш реальный путь
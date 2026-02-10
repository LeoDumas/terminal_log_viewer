cmake_minimum_required(VERSION 3.14)
project(TerminalLogViewer VERSION 1.0  LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)

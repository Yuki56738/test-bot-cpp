cmake_minimum_required(VERSION 3.17)
project(test_bot_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_bot_cpp main.cpp
        commands/ping.cpp
        commands/ping.h
)
add_subdirectory(cpp-dotenv)
target_link_libraries(${PROJECT_NAME}
        dpp
        cpp_dotenv
)
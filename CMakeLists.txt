cmake_minimum_required(VERSION 3.17)
project(test_bot_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_bot_cpp main.cpp
        commands/ping.cpp
        commands/ping.h
        commands/join.cpp
        commands/join.h
        commands/leave.cpp
        commands/leave.h
        voice_generator.cpp
        voice_generator.h
)
add_subdirectory(cpp-dotenv)
find_package(cpprestsdk REQUIRED)

target_link_libraries(${PROJECT_NAME}
        dpp
        cpp_dotenv
        cpprestsdk::cpprest
        crypto
)


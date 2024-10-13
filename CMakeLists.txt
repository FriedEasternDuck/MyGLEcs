    cmake_minimum_required(VERSION 3.29)
    project(untitled1)

    set(CMAKE_CXX_STANDARD 23)

    include_directories("/home/rooster/.vcpkg-clion/vcpkg (1)/installed/x64-linux/include/")

    # Add the shared library
    add_library(untitled1 SHARED
            EntityFactory.cpp
            EntityFactory.h
            ComponentArray.h
            ComponentManager.cpp
            ComponentManager.h
            Components.h
            MyWindow.cpp
            MyWindow.h
            Primitives.h
            World.cpp
            World.h
            Buffers.cpp
            Buffers.h
            Shader.h
            Texture.h
            Input.cpp
            Input.h
            EntityManager.h
            fwd.h
            MovementSystem.cpp
            MovementSystem.h
            ReferanceCubes.hpp
            Camera.hpp
            Components.cpp
    )

    find_package(glad CONFIG REQUIRED)
    target_link_libraries(untitled1 PRIVATE glad::glad)
    find_package(glm CONFIG REQUIRED)
    target_link_libraries(untitled1 PRIVATE glm::glm)
    find_package(glfw3 CONFIG REQUIRED)
    target_link_libraries(untitled1 PRIVATE glfw)
    find_package(Stb REQUIRED)
    target_include_directories(untitled1 PRIVATE ${Stb_INCLUDE_DIR})
    # Add executable and link it to the shared library

    add_executable(libtest main.cpp)
    target_link_libraries(libtest PRIVATE untitled1)


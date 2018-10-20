cmake_minimum_required (VERSION 3.1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (BearBones)
set (PATH_TO_DEPS ${CMAKE_SOURCE_DIR}/deps CACHE PATH "Path to dependency directory")
set (SOURCES "")
set (HEADERS "")
set(CMAKE_SUPPRESS_REGENERATION true)

include_directories (${PATH_TO_DEPS}/include)

add_subdirectory("${CMAKE_SOURCE_DIR}/src/Collision")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Core")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Input")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Objects")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Physics")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Rendering")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Shaders")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/Util")

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(BearBones STATIC ${SOURCES} ${HEADERS})

set_target_properties(BearBones PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(BearBones
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)

add_compile_definitions(NDEBUG)
add_compile_definitions(_ENABLE_EXTENDED_ALIGNED_STORAGE)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)

project(Game)
include_directories (${PATH_TO_DEPS}/include ${CMAKE_SOURCE_DIR}/src)

add_executable(Game ${CMAKE_SOURCE_DIR}/project/game.cpp)
target_link_libraries(Game BearBones)
target_link_libraries(
    Game ${PATH_TO_DEPS}/lib/assimp-vc140-mt.lib
    ${PATH_TO_DEPS}/lib/freeglut.lib
    ${PATH_TO_DEPS}/lib/glew32.lib
    ${PATH_TO_DEPS}/lib/IrrXML.lib
    ${PATH_TO_DEPS}/lib/SOIL.lib
    ${PATH_TO_DEPS}/lib/zlibd.lib
    ${PATH_TO_DEPS}/lib/BulletCollision.lib
    ${PATH_TO_DEPS}/lib/BulletDynamics.lib
    ${PATH_TO_DEPS}/lib/LinearMath.lib
)
set_target_properties(Game
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)

add_custom_command(TARGET Game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PATH_TO_DEPS}/dll $<TARGET_FILE_DIR:Game>)

add_custom_command(TARGET Game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res)

add_custom_command(TARGET Game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/bin/$<CONFIG>/res)
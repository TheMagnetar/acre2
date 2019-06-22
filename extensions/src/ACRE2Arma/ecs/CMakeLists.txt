file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

acre_set_linker_options()

file(GLOB SRC_MAIN "*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
source_group("main" FILES ${SRC_MAIN})

add_library(acre_ecs_static STATIC ${GLOBAL_SOURCES} ${SOURCES})
set_target_properties (acre_ecs_static PROPERTIES CXX_STANDARD 17)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(acre_ecs_static acre_controller_static acre_common ${LINK_LIBS})
set_target_properties(acre_ecs_static PROPERTIES PREFIX "")
set_target_properties(acre_ecs_static PROPERTIES COMPILE_DEFINITIONS _STATIC)
set_target_properties(acre_ecs_static PROPERTIES FOLDER ACRE2Arma)

if(CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(acre_ecs_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(acre_ecs_static PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(acre_ecs_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(acre_ecs_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()

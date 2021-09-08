target_include_directories(Skid PUBLIC "./../Lib/")

### Index ###

add_subdirectory(Index2)

target_include_directories(Skid PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Index2/Index/Include/Include_Index/")
# target_link_libraries(Skid PUBLIC $<TARGET_OBJECTS:Index>)

target_sources(Skid PUBLIC lib.horion.h)


### Horion ###

file(GLOB_RECURSE HorionFiles
        "*.h"
        "*.cpp")

add_library(HorionLibrary STATIC ${HorionFiles})
target_include_directories(HorionLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Horion/include/")
target_include_directories(HorionLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Horion/include/glm/")
target_link_directories(HorionLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Horion/minhook/")
target_link_libraries(Skid PUBLIC HorionLibrary)

### MinHook ###

add_subdirectory(MinHook)

target_link_libraries(HorionLibrary PUBLIC minhook)
target_link_libraries(Skid PUBLIC minhook)
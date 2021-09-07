target_include_directories(Skid PUBLIC "./../Lib/")

### Index ###

add_subdirectory(Index2)

target_include_directories(Skid PUBLIC "Index2/Index/Include/Include_Index/")
target_link_libraries(Skid PUBLIC $<TARGET_OBJECTS:Index>)

target_sources(Skid PUBLIC lib.horion.h)


### Horion ###

target_sources(Skid PUBLIC lib.horion.h)
target_link_directories(Skid PUBLIC Horion/minhook)
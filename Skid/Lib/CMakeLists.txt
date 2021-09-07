### Index ###

add_subdirectory(Index2)

target_include_directories(Skid PUBLIC "Index2/Index/Include/Include_Index/")
target_link_libraries(Skid PUBLIC $<TARGET_OBJECTS:Index>)
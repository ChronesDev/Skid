add_subdirectory(Controls)
add_subdirectory(Renderer)
add_subdirectory(Utils)

target_sources(Skid PUBLIC
        Include.h
        InUI.cc
        Utils.h)
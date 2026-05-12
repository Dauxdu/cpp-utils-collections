project(menu LANGUAGES CXX)

add_library(menu)

target_sources(menu
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    src/MenuLab.cppm
)

#target_compile_features(menu PUBLIC cxx_std_23)

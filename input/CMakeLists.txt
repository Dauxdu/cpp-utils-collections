project(inx LANGUAGES CXX)

add_library(inx)

target_sources(inx
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    src/inx.cppm
    src/InputHelper.cppm
    src/InputNumeric.cppm
    src/InputString.cppm
)

project(nin LANGUAGES CXX)

add_library(nin)

target_sources(nin
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    src/InputNumeric.cppm
)

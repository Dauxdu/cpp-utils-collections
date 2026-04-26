project(nin LANGUAGES CXX)

add_library(nin)

target_sources(nin
    PUBLIC
    FILE_SET CXX_MODULES
    FILES src/InputNumerics.cppm
)

target_compile_features(nin PUBLIC cxx_std_23)

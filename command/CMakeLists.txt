project(cmd LANGUAGES CXX)

add_library(cmd)

target_sources(cmd
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    src/ICommand.cppm
    src/CommandErase.cppm
    src/CommandHistory.cppm
    src/CommandInsert.cppm
)

target_compile_features(cmd PUBLIC cxx_std_23)

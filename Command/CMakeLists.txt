project(cmd LANGUAGES CXX)

add_library(cmd)

target_sources(cmd
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    interface/ICommand.cppm
    src/CommandHistory.cppm
    implementations/EraseCommand.cppm
    implementations/InsertCommand.cppm
)

target_compile_features(cmd PUBLIC cxx_std_23)

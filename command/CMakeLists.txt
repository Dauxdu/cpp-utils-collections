project(cmd LANGUAGES CXX)

add_library(cmd)

target_sources(cmd
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    src/cmd.cppm
    src/ICommand.cppm
    src/CommandClear.cppm
    src/CommandErase.cppm
    src/CommandHistory.cppm
    src/CommandInsert.cppm
    src/CommandSwap.cppm
    src/CommandUpdate.cppm
)

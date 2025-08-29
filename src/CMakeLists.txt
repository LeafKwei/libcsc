set(CSC_SRC
    context/Context.cpp
    core/CscEditor.cpp
    core/CscHandler.cpp
    core/CscStrSeeker.cpp
    lex/CharMngr.cpp
    lex/Lexer.cpp
    lex/Locator.cpp
    lex/PureLexer.cpp
    lex/readers.cpp
    syntax/CommandDrv.cpp
    syntax/cmds.cpp
    utility/utility.cpp
)

include_directories(
    ../include
)

add_library(csc
    ${CSC_SRC}
)
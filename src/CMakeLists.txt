set(CSC_SRC
	action/ActionHub.cpp
    context/Context.cpp
	context/Detector.cpp
	context/ValueMaker.cpp
    core/CscEditor.cpp
    core/CscHandler.cpp
    core/CscStrSeeker.cpp
	core/PathHelper.cpp
    lex/CharMngr.cpp
    lex/Lexer.cpp
    lex/Locator.cpp
    lex/PureLexer.cpp
    lex/readers.cpp
    syntax/CmdDriver.cpp
	syntax/CmdExecutor.cpp
    syntax/commands.cpp
	syntax/Operand.cpp
    utility/utility.cpp
)

include_directories(
    ../include
)

add_library(csc
    ${CSC_SRC}
)
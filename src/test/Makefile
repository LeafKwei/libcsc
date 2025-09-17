extra=-g -Wall
incl=../../include
test_command.exe.src=test_command.cpp ../syntax/CmdContainer.cpp
test_editor.exe.src=test_editor.cpp ../context/Context.cpp ../core/CscStrSeeker.cpp ../core/CscHandler.cpp ../core/CscEditor.cpp  ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/cmds.cpp ../syntax/CommandDrv.cpp ../utility/utility.cpp
test_handler.exe.src=test_handler.cpp ../context/Context.cpp ../core/CscStrSeeker.cpp ../core/CscHandler.cpp ../core/CscEditor.cpp  ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/cmds.cpp ../syntax/CommandDrv.cpp ../utility/utility.cpp
test_func.exe.src=test_func.cpp
test_iterator.exe.src=test_iterator.cpp ../context/Context.cpp ../core/CscStrSeeker.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/cmds.cpp ../syntax/CommandDrv.cpp ../utility/utility.cpp
test_context.exe.src=test_context.cpp ../context/Context.cpp
test_drv.exe.src=test_drv.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/cmds.cpp ../syntax/CommandDrv.cpp  ../context/Context.cpp ../utility/utility.cpp
test_lexer.exe.src=test_lexer.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp
test_ptr.exe.src=test_ptr.cpp

test_command: $(test_command.exe.src)
	g++ $(extra) -o test_command -I $(incl) $(test_command.exe.src)
test_editor.exe: $(test_editor.exe.src)
	g++ $(extra) -o test_editor -I $(incl) $(test_editor.exe.src)
test_handler.exe: $(test_handler.exe.src)
	g++ $(extra) -o test_handler -I $(incl) $(test_handler.exe.src)
test_func.exe.src: $(test_func.exe.src)
	g++ $(extra) -o test_func -I $(incl) $(test_func.exe.src)
test_iterator.exe: $(test_iterator.exe.src)
	g++ $(extra) -o test_iterator -I $(incl) $(test_iterator.exe.src)
test_context.exe: $(test_context.exe.src)
	g++ $(extra) -o test_context -I $(incl) $(test_context.exe.src)
test_drv.exe: $(test_drv.exe.src)
	g++ $(extra) -o test_drv -I $(incl) $(test_drv.exe.src)
test_lexer.exe: $(test_lexer.exe.src)
	g++ $(extra) -o test_lexer -I $(incl) $(test_lexer.exe.src)

clean:
	del test_command.exe
	del test_editor.exe
	del test_handler.exe
	del test_func.exe
	del test_iterator.exe
	del test_drv.exe
	del test_lexer.exe
	del test_context.exe
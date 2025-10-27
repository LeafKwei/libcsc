extra=-g -Wall
incl=../../include
test_editor.exe.src=test_editor.cpp ../context/Context.cpp ../context/Detector.cpp ../core/CscStrSeeker.cpp ../core/CscHandler.cpp ../core/CscEditor.cpp ../core/PathHelper.cpp  ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/commands.cpp ../syntax/CmdDriver.cpp ../syntax/CmdExecutor.cpp ../syntax/Operand.cpp ../context/ValueMaker.cpp   ../utility/utility.cpp ../action/ActionMngr.cpp
test_handler.exe.src=test_handler.cpp ../context/Context.cpp ../context/Detector.cpp ../core/CscStrSeeker.cpp ../core/CscHandler.cpp ../core/CscEditor.cpp ../core/PathHelper.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/commands.cpp ../syntax/Operand.cpp ../context/ValueMaker.cpp  ../syntax/CmdDriver.cpp ../syntax/CmdExecutor.cpp ../utility/utility.cpp ../action/ActionMngr.cpp
test_func.exe.src=test_func.cpp ../core/PathHelper.cpp
test_iterator.exe.src=test_iterator.cpp ../context/Context.cpp ../context/Detector.cpp ../core/CscStrSeeker.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/commands.cpp ../syntax/CmdDriver.cpp ../syntax/Operand.cpp ../context/ValueMaker.cpp  ../syntax/CmdExecutor.cpp ../utility/utility.cpp ../action/ActionMngr.cpp
test_context.exe.src=test_context.cpp ../context/Context.cpp ../context/Detector.cpp
test_drv.exe.src=test_drv.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/Operand.cpp ../context/ValueMaker.cpp  ../context/ValueMaker.cpp  ../syntax/commands.cpp ../syntax/CmdDriver.cpp ../syntax/CmdExecutor.cpp  ../context/Context.cpp ../context/Detector.cpp ../utility/utility.cpp ../action/ActionMngr.cpp
test_lexer.exe.src=test_lexer.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../utility/utility.cpp
test_ptr.exe.src=test_ptr.cpp

test_editor.exe: $(test_editor.exe.src)
	g++ $(extra) -o test_editor -I $(incl) $(test_editor.exe.src)
test_handler.exe: $(test_handler.exe.src)
	g++ $(extra) -o test_handler -I $(incl) $(test_handler.exe.src)
test_func.exe: $(test_func.exe.src)
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
	del test_editor.exe
	del test_handler.exe
	del test_func.exe
	del test_iterator.exe
	del test_drv.exe
	del test_lexer.exe
	del test_context.exe
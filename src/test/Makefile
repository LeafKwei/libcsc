extra=-g
incl=../../include
test_context.exe.src=test_context.cpp ../context/Context.cpp
test_drv.exe.src=test_drv.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/cmds.cpp ../syntax/CommandDrv.cpp  ../context/Context.cpp ../utility/utility.cpp
test_lexer.exe.src=test_lexer.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp
test_ptr.exe.src=test_ptr.cpp

test_context.exe: $(test_context.exe.src)
	g++ $(extra) -o test_context -I $(incl) $(test_context.exe.src)
test_drv.exe: $(test_drv.exe.src)
	g++ $(extra) -o test_drv -I $(incl) $(test_drv.exe.src)
test_lexer.exe: $(test_lexer.exe.src)
	g++ $(extra) -o test_lexer -I $(incl) $(test_lexer.exe.src)
test_ptr.exe: $(test_ptr.exe.src)
	g++ $(extra)  -o test_ptr.exe $(test_ptr.exe.src)

clean:
	del test_drv.exe
	del test_lexer.exe
	del test_context.exe
	del test_ptr.exe
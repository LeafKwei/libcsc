extra=-g
incl=../../include
test_iterator.exe.src=test_iterator.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/cmds.cpp ../syntax/CommandDrv.cpp  ../context/Context.cpp ../utility/utility.cpp
test_value.exe.src=test_value.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../utility/utility.cpp
test_drv.exe.src=test_drv.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp ../syntax/cmds.cpp ../syntax/CommandDrv.cpp  ../context/Context.cpp ../utility/utility.cpp
test_lexer.exe.src=test_lexer.cpp ../lex/CharMngr.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/PureLexer.cpp
test_ptr.exe.src=test_ptr.cpp
test_context.exe.src=test_context.cpp ../context/Context.cpp ../utility/utility.cpp
test_ctor.exe.src=test_ctor.cpp ../context/Context.cpp ../utility/utility.cpp
test_attach.exe.src=test_attach.cpp ../context/Context.cpp ../utility/utility.cpp
test_builtin.exe.src=test_builtin.cpp ../context/Context.cpp ../utility/utility.cpp
test_reset.exe.src=test_reset.cpp ../context/Context.cpp ../utility/utility.cpp

test_iterator.exe: $(test_iterator.exe.src)
	g++ $(extra) -o test_iterator -I $(incl) $(test_iterator.exe.src)
test_value.exe: $(test_value.exe.src)
	g++ $(extra) -o test_value -I $(incl) $(test_value.exe.src)
test_drv.exe: $(test_drv.exe.src)
	g++ $(extra) -o test_drv -I $(incl) $(test_drv.exe.src)
test_lexer.exe: $(test_lexer.exe.src)
	g++ $(extra) -o test_lexer -I $(incl) $(test_lexer.exe.src)
test_reset.exe: $(test_reset.exe.src)
	g++ $(extra) -o test_reset -I $(incl) $(test_reset.exe.src)
test_builtin.exe: $(test_builtin.exe.src)
	g++ $(extra) -o test_builtin -I $(incl) $(test_builtin.exe.src)
test_ctor.exe: $(test_ctor.exe.src)
	g++ $(extra) -o test_ctor -I $(incl) $(test_ctor.exe.src)
test_attach.exe: $(test_attach.exe.src)
	g++ $(extra) -o test_attach -I $(incl) $(test_attach.exe.src)
test_context.exe: $(test_context.exe.src)
	g++ $(extra) -o test_context -I $(incl) $(test_context.exe.src)
test_ptr.exe: $(test_ptr.exe.src)
	g++ $(extra)  -o test_ptr.exe $(test_ptr.exe.src)

clean:
	del test_iterator.exe
	del test_drv.exe
	del test_lexer.exe
	del test_reset.exe
	del test_builtin.exe
	del test_ctor.exe
	del test_attach.exe
	del test_context.exe
	del test_ptr.exe
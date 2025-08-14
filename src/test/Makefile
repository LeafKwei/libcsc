extra=-g
incl=../../include
test_lexer.exe.src=test_lexer.cpp ../lex/CharMngr.cpp ../lex/functions.cpp ../lex/Lexer.cpp ../lex/Locator.cpp ../lex/readers.cpp ../lex/ctrls.cpp
test_ptr.exe.src=test_ptr.cpp
test_context.exe.src=test_context.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp
test_ctor.exe.src=test_ctor.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp
test_attach.exe.src=test_attach.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp
test_builtin.exe.src=test_builtin.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp
test_reset.exe.src=test_reset.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp

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
	del test_lexer.exe
	del test_reset.exe
	del test_builtin.exe
	del test_ctor.exe
	del test_attach.exe
	del test_context.exe
	del test_ptr.exe
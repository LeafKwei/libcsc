extra=-g
incl=../../include
test_find.exe.src=test_find.cpp
test_lex.exe.src=test_lex.cpp ../lex/readers.cpp  ../syntax/readers.cpp ../lex/LexHelper.cpp
test_ptr.exe.src=test_ptr.cpp
test_split.exe.src=test_split.cpp ../utility/utility.cpp ../core/path.cpp
test_context.exe.src=test_context.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp
test_ctor.exe.src=test_ctor.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp
test_attach.exe.src=test_attach.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp
test_builtin.exe.src=test_builtin.cpp ../core/Dcontext.cpp ../utility/utility.cpp ../core/path.cpp

test_builtin.exe: $(test_builtin.exe.src)
	g++ -o $(extra) -o test_builtin -I $(incl) $(test_builtin.exe.src)
test_ctor.exe: $(test_ctor.exe.src)
	g++ $(extra) -o test_ctor -I $(incl) $(test_ctor.exe.src)
test_attach.exe: $(test_attach.exe.src)
	g++ $(extra) -o test_attach -I $(incl) $(test_attach.exe.src)
test_context.exe: $(test_context.exe.src)
	g++ $(extra) -o test_context -I $(incl) $(test_context.exe.src)
test_find.exe: $(test_find.exe.src)
	g++ $(extra)  -o test_find -I ${incl} $(test_find.exe.src)
test_lex.exe: $(test_lex.exe.src)
	g++ $(extra)  -o test_lex.exe -I $(incl) $(test_lex.exe.src)
test_ptr.exe: $(test_ptr.exe.src)
	g++ $(extra)  -o test_ptr.exe $(test_ptr.exe.src)
test_split.exe: $(test_split.exe.src)
	g++ $(extra)  -o test_split.exe -I $(incl) $(test_split.exe.src)

clean:
	del test_builtin.exe
	del test_ctor.exe
	del test_attach.exe
	del test_context.exe
	del test_find.exe
	del test_lex.exe
	del test_ptr.exe
	del test_split.exe
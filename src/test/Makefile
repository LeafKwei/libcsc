incl=../../include
test_find.exe.src=test_find.cpp
test_lex.exe.src=test_lex.cpp ../lex/readers.cpp  ../syntax/readers.cpp ../lex/LexHelper.cpp
test_ptr.exe.src=test_ptr.cpp
test_split.exe.src=test_split.cpp
test_context.exe.src=test_context.cpp ../core/Dcontext.cpp ../utility/utility.cpp

test_context.exe: $(test_context.exe.src)
	g++ -o test_context -I $(incl) $(test_context.exe.src)
test_find.exe: $(test_find.exe.src)
	g++ -o test_find -I ${incl} $(test_find.exe.src)
test_lex.exe: $(test_lex.exe.src)
	g++ -o test_lex.exe -I $(incl) $(test_lex.exe.src)
test_ptr.exe: $(test_ptr.exe.src)
	g++ -o test_ptr.exe $(test_ptr.exe.src)
test_split.exe: $(test_func.exe.src)
	g++ -o test_func.exe $(test_func.exe.src)

clean:
	del test_context.exe
	del test_find.exe
	del test_lex.exe
	del test_ptr.exe
	del test_func.exe
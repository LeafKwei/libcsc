incl=../../include
main.exe.src=main.cpp ../lex/readers.cpp  ../syntax/readers.cpp ../lex/LexHelper.cpp

main.exe: $(main.exe.src)
	g++ -o main.exe -I $(incl) $(main.exe.src)

clean:
	del main.exe
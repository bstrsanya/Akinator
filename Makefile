FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
CC=g++ -DTYPEDEF
QQ=-I./include -I./lib -I./Stack/include -c

all: hello

hello: main.o Akinator.o ReadFile.o SizeFile.o stack.o
	$(CC) main.o Akinator.o ReadFile.o SizeFile.o stack.o $(FLAGS) -o main

main.o: src/main.cpp
	$(CC) $(QQ) src/main.cpp

Akinator.o: src/Akinator.cpp
	$(CC) $(QQ) src/Akinator.cpp

ReadFile.o: lib/ReadFile.cpp
	$(CC) $(QQ) lib/ReadFile.cpp

SizeFile.o: lib/SizeFile.cpp
	$(CC) $(QQ) lib/SizeFile.cpp

stack.o: Stack/src/stack.cpp
	$(CC) $(QQ) Stack/src/stack.cpp

clean:
	rm -rf *.o hello
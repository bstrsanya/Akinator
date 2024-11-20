CC = g++
COMMONINC = -I./include -I./lib -I./Stack/include
CFLAGS ?= -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
OUT_O_DIR := obj

CSRC = ./src/main.cpp ./src/Akinator.cpp ./src/GenericFunc.cpp ./src/GraphDump.cpp ./lib/ReadFile.cpp ./lib/SizeFile.cpp ./Stack/src/stack.cpp
override CFLAGS += $(COMMONINC)

COBJ := $(addprefix $(OUT_O_DIR)/, $(CSRC:%.cpp=%.o)) 
DEPS := $(COBJ:%.o=%.d) 

.PHONY: all Release Debug  сlean
all: $(OUT_O_DIR)/main
Release: $(OUT_O_DIR)/main
Debug: $(OUT_O_DIR)/main

сlean:
	rm $(COBJ) $(DEPS) 
	
$(OUT_O_DIR)/main : $(COBJ)
	@$(CC) $^ -o $@ $(CFLAGS)

$(COBJ): $(OUT_O_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $<  -o $@

$(DEPS): $(OUT_O_DIR)/%.d : %.cpp
	@mkdir -p $(@D)
	@$(CC) -E $(CFLAGS) $< -MM -MT $(@:%.d=%.o) > $@
CXX=g++
CC=gcc
LEX=flex
YACC=bison
LD=gcc

OBJ_FILES = def.tab.o lex.yy.o asmgen.o utils.o generation_utils.o def_utils.o

all: leks

leks: $(OBJ_FILES)
	$(CXX) -std=c++11 $(OBJ_FILES) -o leks -ll
	rm -f $(OBJ_FILES)

lex.yy.o: lex.yy.c
	$(CXX) -c lex.yy.c

lex.yy.c: zX.l
	$(LEX) zX.l

def.tab.o: def.tab.cc
	$(CXX) -std=c++11 -c def.tab.cc

def.tab.cc: def.yy
	$(YACC) -d def.yy

asmgen.o: asmgen.cpp utils.h generation_utils.h symbol.h
	$(CXX) -std=c++11 -c asmgen.cpp

utils.o: utils.cpp utils.h symbol.h
	$(CXX) -std=c++11 -c utils.cpp

generation_utils.o: generation_utils.cpp generation_utils.h symbol.h
	$(CXX) -std=c++11 -c generation_utils.cpp

def_utils.o: def_utils.cpp def_utils.h def_globals.h symbol.h
	$(CXX) -std=c++11 -c def_utils.cpp

clean:
	rm -f *.o leks def.tab.cc lex.yy.c

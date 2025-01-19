all:
	bison -d -o grammar/grammar.tab.cc grammar/grammar.y -Wcounterexamples
	flex -o grammar/lex.yy.cc grammar/grammar.l 
	g++ driver/driver.cc grammar/lex.yy.cc grammar/grammar.tab.cc AST/Node.cc main.cpp -g -lfl -o zmm

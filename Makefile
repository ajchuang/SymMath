all:
	@g++ -g -std=c++0x -I./inc ./src/sym_expr.cc ./src/main.cc -o main 

clean:
	@rm -f main

Compiler = g++ -std=c++14 -Wall -Wextra -Wpedantic -g

Node.o: Node.cpp
	$(Compiler) -c Node.cpp

IsBST: Node.o IsBSTTask.cpp
	$(Compiler) Node.o IsBSTTask.cpp
	./a.out

IsFull: Node.o IsFullTask.cpp
	$(Compiler) Node.o IsFullTask.cpp
	./a.out

ReduceToBST: Node.o ReduceToBSTTask.cpp
	$(Compiler) Node.o ReduceToBSTTask.cpp
	./a.out

clean:
	rm *.o ./a.out
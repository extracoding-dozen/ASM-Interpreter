build:
	g++ -Wall -Wextra -c VariableMemory.cpp -fsanitize=address -o VariableMemory.o -g
	g++ -Wall -Wextra -c tests.cpp -fsanitize=address -o tests.o -lgtest -g
	g++ *.o -fsanitize=address -lgtest -o bin_asan
	rm *.o


build_coverage:
	g++ --coverage -Wall -Wextra -c VariableMemory.cpp -o VariableMemory.o
	g++ --coverage -Wall -Wextra -c tests.cpp -o tests.o -lgtest
	g++ --coverage *.o -lgtest -o bin_asan
	rm *.o
build:
	g++ -Wall -Wextra -c testingMult.cpp -fsanitize=address,undefined -o tests.o -g -lgtest
	g++ -Wall -Wextra -c ../../RegisterBlock/RegisterBlock.cpp -fsanitize=address,undefined -o RB.o -g -lgtest
	g++ -Wall -Wextra -c ../../VariableMemory/VariableMemory.cpp -fsanitize=address,undefined -o VM.o -g -lgtest
	g++ *.o -fsanitize=address,undefined -o bin_asan -lgtest -g
	rm *.o

build_coverage:
	g++ --coverage -c testingMult.cpp -o tests.o -lgtest -g
	g++ -I ../../RegisterBlock --coverage  -c ../../RegisterBlock/RegisterBlock.cpp -o RB.o -g
	g++ -I ../../VariableMemory --coverage  -c ../../VariableMemory/VariableMemory.cpp -o VM.o -g
	g++ --coverage *.o -o bin_testing -lgtest -g
	rm *.o
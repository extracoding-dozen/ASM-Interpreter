build_asan_W:
	g++ -Wall -Wextra -c CP.cpp -fsanitize=address -o CP.o -g
	g++ -Wall -Wextra -c Core/Core.cpp -fsanitize=address -o Core.o -g
	g++ -Wall -Wextra -c Core/Programm/Programm.cpp -fsanitize=address -o Prog.o -g
	g++ -Wall -Wextra -c Core/RegisterBlock/RegisterBlock.cpp -fsanitize=address -o RB.o -g
	g++ -Wall -Wextra -c Core/VariableMemory/VariableMemory.cpp -fsanitize=address -o VM.o -g 
	ar rc libCentralProcessor.a *.o -g
	rm *.o

build_asan:
	g++ -c CP.cpp -fsanitize=address -O0 -o CP.o -g
	g++ -c Core/Core.cpp -fsanitize=address -O0 -o Core.o -g
	g++ -c Core/Programm/Programm.cpp -fsanitize=address -O0 -o Prog.o -g
	g++ -c Core/RegisterBlock/RegisterBlock.cpp -fsanitize=address -O0 -o RB.o -g
	g++ -c Core/VariableMemory/VariableMemory.cpp -fsanitize=address -O0 -o VM.o -g 
	g++ -c Validator/Validator.cpp -fsanitize=address -O0 -o valid.o -g
	g++ -c main.cpp -fsanitize=address -O0 -o main.o -g
	g++ *.o -fsanitize=address -o bin_asan -g
	rm *.o
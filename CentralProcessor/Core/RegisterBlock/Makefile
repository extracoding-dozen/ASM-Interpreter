build:
	g++ -Wall -Wextra -c RegisterBlock.cpp -fsanitize=address -o RegisterBlock.o -g
	g++ -Wall -Wextra -c tests.cpp -fsanitize=address -o tests.o -lgtest -g
	g++ *.o -fsanitize=address -lgtest -o bin_asan
	rm *.o


build_coverage:
	g++ --coverage -Wall -Wextra -c RegisterBlock.cpp -o RegisterBlock.o
	g++ --coverage -Wall -Wextra -c tests.cpp -o tests.o -lgtest
	g++ --coverage *.o -lgtest -o bin_asan
	rm *.o
.PHONY: test clean mutate coverage main analyze

main:
	@echo "Compiling main program..."
	g++ LibraryManagementSystem.cpp -o main

test:
	@echo "Running tests..."
	make clean
	rm -rf tests
	mkdir tests
	g++ LibraryManagementSystem.cpp test.cpp -o test -ldeepstate
	./test --fuzz --timeout 10 --output_test_dir=tests -vv

mutate:
	@echo "Running mutation tests..."
	make clean
	rm -rf mutants
	mkdir mutants
	mutate LibraryManagementSystem.cpp --mutantDir mutants --cmd "g++ LibraryManagementSystem.cpp -c"

analyze:
	@echo "Analyzing mutation tests..."
	analyze_mutants LibraryManagementSystem.cpp --mutantDir mutants "g++ LibraryManagementSystem.cpp test.cpp -o test -ldeepstate && ./test --fuzz --timeout 1" --timeout 5

coverage:
	@echo "Running coverage tests..."
	make clean
	rm -rf coverage
	mkdir coverage
	g++ -O1 -fprofile-arcs -ftest-coverage test.cpp LibraryManagementSystem.cpp -o test -ldeepstate -lgcov
	./test --fuzz --timeout 10 --output_test_dir=coverage -vv
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/include/*' '/usr/local/include/*' -o coverage.info

clean:
	@echo "Cleaning up..."
	rm -rf test main mutants tests coverage coverage.info
	rm -f *.gcda *.gcno

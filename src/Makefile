FLAGS =-Wall -Werror -Wextra -std=c++17 -pedantic
TEST_FLAGS= -lgtest -lstdc++ --coverage 

all: clean s21_matrix_oop.a test

s21_matrix_oop.o: s21_matrix_oop.cpp
	g++ -c $(FLAGS) s21_matrix_oop.cpp

test.o: test.cpp
	g++ -c $(FLAGS) test.cpp

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o

test: test.o s21_matrix_oop.a 
	g++  test.o s21_matrix_oop.a -o test $(TEST_FLAGS)
	./test

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test

leaks: test
	leaks -atExit -- ./test
	
style: 
	cp ../materials/linters/.clang-format .
	clang-format -i *.cpp *.h
	clang-format -n *.cpp *.h

clean:
	rm -rf *.o *.a test *.gcno

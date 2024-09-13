CC=g++
FLAGS=-std=c++17 -g -Wall -Werror -Wextra
COVFLAGS = -fprofile-arcs  -lcheck -ftest-coverage
TARGET = s21_matrix_oop
LIBNAME = $(TARGET).a
SRC = s21_matrix_oop.cc

# с целями all, clean, test, s21_matrix_oop.a
all: $(LIBNAME)

gcov_report: test
	gcov -f *.gcda
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=0
	genhtml -o report test.info  --rc lcov_branch_coverage=0
	open report/index.html

test: clean $(LIBNAME)
		$(CC) -c test.cc 
		$(CC) --coverage -o test.out test.o -lgtest -lgtest_main -L. s21_matrix_oop.a
		./test.out

$(LIBNAME): s21_matrix_oop.o
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

s21_matrix_oop.o:
		$(CC) -c $(COVFLAGS) $(SRC)

leaks: clean test
		leaks -atExit -- ./test.out

cppcheck:
		cppcheck --enable=all --suppress=missingIncludeSystem *.cc

style:
		@cp ../materials/linters/.clang-format .
		clang-format -n *.cc *.h
		@rm -rf .clang-format

make_style:
		@cp ../materials/linters/.clang-format .
		clang-format -i *.cc *.h
		@rm -rf .clang-format

valgrind: $(LIBNAME)
	valgrind ./test.out

clean:
		@rm -rf *.out *.o *.a *.gcov *.gcda *.gcno *.info report log_valgrind
		rm -rf *.gcno *.html report doxygen *.gcov *.gcda $(TESTS) *.a *.info *.o *.out 
		rm -rf test.dSYM a.out.dSYM test.dSYM

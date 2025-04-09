CC=g++
CC_FLAGS=-Wall -Werror -Wextra -std=c++17
CC_test=-fprofile-arcs -ftest-coverage -fno-elide-constructors -fno-default-inline
TESTS_FOLDER=tests/
LDFLAGS=$(shell pkg-config --libs gtest_main)

all: gcov_report

.PHONY: test gcov_report valgrind clean clang

gcov_report: test
	lcov -t "test" -o $(TESTS_FOLDER)test.info -c -d . --no-external --ignore-errors mismatch,mismatch --ignore-errors inconsistent 
	genhtml -o report $(TESTS_FOLDER)test.info
	xdg-open report/index.html

test: clean
	$(CC) $(CC_FLAGS) $(CC_test) */*.cc -o test -lm $(LDFLAGS)
	./test
	mv *.gcda *.gcno $(TESTS_FOLDER)

valgrind: debug
	valgrind --tool=memcheck --leak-check=yes ./debug
	mv *.gcda *.gcno $(TESTS_FOLDER)

debug: clean
	$(CC) -g $(CC_FLAGS) $(CC_test) */*.cc -o debug -lm $(LDFLAGS)

clean:
	rm -f test debug
	rm -f $(TESTS_FOLDER)*.gcda $(TESTS_FOLDER)*.gcno $(TESTS_FOLDER)test.info
	rm -rf report

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.h */*.cc */*.h */*.tpp
	rm -f .clang-format

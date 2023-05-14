MAIN_PROJ_NAME=matrix
FUNCS=$(MAIN_PROJ_NAME).cc
TEST_C=$(FUNCS) $(MAIN_PROJ_NAME)_test.cc
EXECUTABLE=$(MAIN_PROJ_NAME)_test.out
COMPILER=g++
STD=-std=c++17
CPP_FLAGS=-Wall -Wextra -Werror -Wpedantic
TEST_FLAGS=-lgtest -pthread
GCOV_FLAG=--coverage
LINT_WAY=../materials/linters/cpplint.py
LINTCFG=CPPLINT.cfg
LINTCFG_WAY=../materials/linters/$(LINTCFG)
EXTENSION=--extensions=cc
CHECK_FILES=*.cc *.h
CPPCH_SETUP=--enable=warning,performance,portability  -v --language=c++ -$(STD)
TO_DELETE=*.o *.a *.dSYM $(EXECUTABLE) $(LINTCFG) matrix_output.txt
VALGRIND_SETUP=--tool=memcheck --leak-check=full --show-leak-kinds=all


all: check $(MAIN_PROJ_NAME).a test

check:
	cppcheck $(CPPCH_SETUP) $(CHECK_FILES)
	cp $(LINTCFG_WAY) $(LINTCFG)
	python3 $(LINT_WAY) $(EXTENSION) $(CHECK_FILES)

clean:
	rm -rf $(TO_DELETE)

test: clean
	$(COMPILER) $(STD) $(CPP_FLAGS) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	./$(MAIN_PROJ_NAME)_test.out

$(MAIN_PROJ_NAME).a:
	$(COMPILER) -O3 -c $(FUNCS)
	ar rc lib$(MAIN_PROJ_NAME).a $(MAIN_PROJ_NAME).o
	ranlib lib$(MAIN_PROJ_NAME).a

valgrind: clean
	$(COMPILER) $(STD) -g $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_SETUP) ./$(EXECUTABLE)

leaks: test
	leaks -atExit -- ./$(EXECUTABLE)

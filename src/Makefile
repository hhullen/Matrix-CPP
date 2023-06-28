MAIN_PROJ_NAME=matrix
FUNCS=$(MAIN_PROJ_NAME).cc
TEST_C=$(FUNCS) $(MAIN_PROJ_NAME)_test.cc
EXECUTABLE=$(MAIN_PROJ_NAME)_test.out
COMPILER=g++
STD=--std=c++20
CPP_FLAGS=-Wextra -Werror -Wpedantic -Wshadow \
		  -Wconversion -Wnull-dereference -Wsign-conversion
TEST_FLAGS=-lgtest -pthread
GCOV_FLAG=--coverage
LINT_WAY=..$(SEP)materials$(SEP)linters$(SEP)cpplint.py
LINTCFG=CPPLINT.cfg
LINTCFG_WAY=..$(SEP)materials$(SEP)linters$(SEP)$(LINTCFG)
EXTENSION=--extensions=cc
CLANG_FILE=.clang-format
CLANG_FILE_WAY=..$(SEP)materials$(SEP)linters$(SEP)$(CLANG_FILE)
CHECK_FILES=*.cc *.h
CPPCH_SETUP=--enable=warning,performance,portability  -v --language=c++ $(STD)
VALGRIND_SETUP=--tool=memcheck --leak-check=full --show-leak-kinds=all
TO_DELETE_FILES=*.o *.a *.out *.dSYM *.gch *.gcda *.gcno .DS_Store $(EXECUTABLE) \
				$(CLANG_FILE) *.info matrix_output.txt
TO_DELETE_FOLDERS=$(BUILD_DIR) report *.dSYM


#Crossplatform specs
SEP='\'
MAKEDIR=md
DELETE_FOLDER=RD /S/Q
DELETE_FILE=DEL /F
COPY=copy
OPEN=start
OS=$(shell uname)

ifeq ($(OS), Linux)
	OPEN=xdg-open
	MAKEDIR=mkdir -p
	SEP=/
	DELETE_FOLDER=rm -rf
	DELETE_FILE=rm -f
	COPY=cp
endif

ifeq ($(OS), Darwin)
	OPEN=open
	MAKEDIR=mkdir -p
	SEP=/
	DELETE_FOLDER=rm -rf
	DELETE_FILE=rm -f
	COPY=cp
endif


all: check $(MAIN_PROJ_NAME).a tests

check:
	cppcheck $(CPPCH_SETUP) $(CHECK_FILES)
	$(COPY) $(CLANG_FILE_WAY) $(CLANG_FILE)
	clang-format -i --style=Google $(CHECK_FILES)
	clang-format -n --style=Google $(CHECK_FILES)

clean:
	$(DELETE_FOLDER) $(TO_DELETE_FOLDERS)
	$(DELETE_FILE) $(TO_DELETE_FILES)

tests: clean
	$(COMPILER) $(STD) $(CPP_FLAGS) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	.$(SEP)$(MAIN_PROJ_NAME)_test.out

$(MAIN_PROJ_NAME).a:
	$(COMPILER) $(STD) -O3 -c $(FUNCS)
	ar rc lib$(MAIN_PROJ_NAME).a $(MAIN_PROJ_NAME).o

valgrind: clean
	$(COMPILER) $(STD) -g $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_SETUP) .$(SEP)$(EXECUTABLE)

leaks: tests
	leaks -atExit -- .$(SEP)$(EXECUTABLE)

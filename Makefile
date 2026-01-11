TEST_NAME = containers_test
LIB_TARGET = s21_containers.a
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++20
GTEST_FLAGS = -lgtest -lgtest_main -pthread
COVFLAGS = --coverage

PATH_TEST_SRC = ./test/
PATH_TEST_OBJ = ./obj/test/

SRC_TEST = $(wildcard $(PATH_TEST_SRC)*.cpp)
OBJ_TEST = $(patsubst $(PATH_TEST_SRC)%.cpp, $(PATH_TEST_OBJ)%.o, $(SRC_TEST))

$(shell mkdir -p ./obj/lib/)
$(shell mkdir -p ./obj/test/)
$(shell mkdir -p ./report/)

all : s21_containers.a 

s21_containers.a : ./obj/lib/lib.o
	@printf "\033[0;32mbuilding static library...\033[0m\n" >&2
	@ar rcs $(LIB_TARGET) ./obj/lib/lib.o
	@echo "\033[0;32mdone\033[0m"

./obj/lib/lib.o : ./src/lib.cpp
	@$(CXX) $(CXXFLAGS) -c ./src/lib.cpp -o ./obj/lib/lib.o

test : $(OBJ_TEST) 
	@printf "\033[0;32mrunning tests...\033[0m\n" >&2
	$(CXX) $(CXXFLAGS) $(OBJ_TEST) -o $(TEST_NAME) $(COVFLAGS) $(GTEST_FLAGS)
	./$(TEST_NAME) --gtest_color=yes --gtest_brief

gcov_report : test
	@lcov -t "report_containers" -o test.info -c -d ./obj/test/ --ignore-errors gcov
	@lcov --extract test.info '**/src/**' -o test_filtered.info
	@genhtml -o report test_filtered.info
	@open report/index.html

$(PATH_TEST_OBJ)%.o : $(PATH_TEST_SRC)%.cpp
	$(CXX) $(CXXFLAGS) $(COVFLAGS) -c $< -o $@

clean :
	@-rm  $(LIB_TARGET)
	@-rm -rf ./obj/
	@-rm -rf report
	@-rm -rf coverage_all.info coverage_filtered.info test.info test_filtered.info $(TEST_NAME)
	@echo "\033[0;32mcleaning...\033[0m"
	@echo "done"

format :
	find . -name "*.cpp" -o -name "*.h" -o -name "*.tpp" | xargs clang-format -i

check_format :
	find . -name "*.cpp" -o -name "*.h" -o -name "*.tpp" | xargs clang-format -n

valgrind :
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_NAME)


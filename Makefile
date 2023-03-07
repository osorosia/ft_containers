CXX = c++
CXXFLAGS = -std=c++98 -g -Wall -Wextra -Werror
DEPFLAGS = -MMD -MP

TEST_SRCS = $(wildcard src/*.cpp src/*/*.cpp)
TEST_OBJS = $(TEST_SRCS:src/%.cpp=obj/%.o)
DEPS = $(TEST_SRCS:src/%.cpp=obj/%.d)

OBJS_DIR := $(sort $(dir $(TEST_OBJS)))
OBJS_DIR := $(addsuffix .keep, $(OBJS_DIR))

INCS = -Isrc

# subject test
FT_SUBJECT_TEST_NAME = ft_subject_test.out
STD_SUBJECT_TEST_NAME = std_subject_test.out
SUBJECT_TEST_SRC = test/main.cpp

# unit test
UNIT_TEST_NAME = unit_test.out
UNIT_TEST_SRC = test/unit_test.cpp

# bench test
FT_BENCH_TEST_NAME = ft_bench_test.out
STD_BENCH_TEST_NAME = std_bench_test.out
BENCH_TEST_SRC = test/bench_test.cpp
BENCH_CALC_NAME = bench_calc.out
BENCH_CALC_SRC = test/bench_calc.cpp


.PHONY: all
all: unit

-include $(DEPS)

# subject test
$(FT_SUBJECT_TEST_NAME): $(SUBJECT_TEST_SRC) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -D FT $(INCS) -o $@ $^
$(STD_SUBJECT_TEST_NAME): $(SUBJECT_TEST_SRC) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# unit test
$(UNIT_TEST_NAME): $(UNIT_TEST_SRC) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# bench test
$(FT_BENCH_TEST_NAME): $(BENCH_TEST_SRC) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -D FT $(INCS) -o $@ $^
$(STD_BENCH_TEST_NAME): $(BENCH_TEST_SRC) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BENCH_CALC_NAME): $(BENCH_CALC_SRC)
	$(CXX) -o $@ $^

obj/%.o: src/%.cpp $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -o $@ -c $<

$(OBJS_DIR):
	mkdir -p $(@D)
	touch $@

.PHONY: unit u
unit u: $(UNIT_TEST_NAME)
	./$(UNIT_TEST_NAME) > log.md

.PHONY: bench b
bench b: $(FT_BENCH_TEST_NAME) $(STD_BENCH_TEST_NAME) $(BENCH_CALC_NAME)
	./$(FT_BENCH_TEST_NAME) > ft_bench.log
	./$(STD_BENCH_TEST_NAME)  > std_bench.log
	sdiff --width=56 ft_bench.log std_bench.log || true
	./$(BENCH_CALC_NAME)

.PHONY: subject sub
subject sub: $(STD_SUBJECT_TEST_NAME) $(FT_SUBJECT_TEST_NAME)
	./$(FT_SUBJECT_TEST_NAME) 1
	./$(STD_SUBJECT_TEST_NAME) 1

.PHONY: clean c
clean c:
	rm -f $(TEST_OBJS)
	rm -f $(DEPS)


.PHONY: fclean fc
fclean fc: clean
	rm -f $(FT_SUBJECT_TEST_NAME)
	rm -f $(STD_SUBJECT_TEST_NAME)
	rm -f $(UNIT_TEST_NAME)
	rm -f $(FT_BENCH_TEST_NAME)
	rm -f $(STD_BENCH_TEST_NAME)

.PHONY: re
re: fclean all

.PHONY: test
test: $(UNIT_TEST_NAME)
	valgrind ./$(UNIT_TEST_NAME) > log.md

.PHONY: t
t:
	${CXX} -o tmp tmp.cpp
	./tmp


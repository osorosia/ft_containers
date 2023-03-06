CXX = c++
CXXFLAGS = -std=c++98 # -Wall -Wextra -Werror
DEPFLAGS = -MMD -MP

TEST_SRCS = $(wildcard src/*.cpp src/*/*.cpp)
TEST_OBJS = $(TEST_SRCS:src/%.cpp=obj/%.o)
DEPS = $(TEST_SRCS:src/%.cpp=obj/%.d)

OBJS_DIR := $(sort $(dir $(TEST_OBJS)))
OBJS_DIR := $(addsuffix .keep, $(OBJS_DIR))

# unit test
UNIT_TEST_NAME = unit_test.out
UNIT_TEST_OBJ = test/unit_test.o


all: $(UNIT_TEST_NAME)

-include $(DEPS)

$(UNIT_TEST_NAME): $(UNIT_TEST_OBJ) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -o $@ -c $<

$(OBJS_DIR):
	mkdir -p $(@D)
	touch $@

clean:
	rm -f $(TEST_OBJS)
	rm -f $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(UNIT_TEST_NAME)
	./$(UNIT_TEST_NAME) > log.md

debug deb: $(TEST_NAME)
	valgrind ./$(TEST_NAME) > log.md

t:
	${CXX} -o tmp tmp.cpp
	./tmp

.PHONY: all clean fclean re test

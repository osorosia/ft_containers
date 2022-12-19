CXX = c++
CXXFLAGS = -std=c++98 # -Wall -Wextra -Werror
DEPFLAGS = -MMD -MP

TEST_NAME = test.out
TEST_SRCS = $(wildcard src/*.cpp)
TEST_OBJS = $(TEST_SRCS:src/%.cpp=obj/%.o)
DEPS = $(TEST_SRCS:src/%.cpp=obj/%.d)

OBJS_DIR := $(sort $(dir $(TEST_OBJS)))
OBJS_DIR := $(addsuffix .keep, $(OBJS_DIR))

all: $(TEST_NAME)

-include $(DEPS)

$(TEST_NAME): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS)

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

test: $(TEST_NAME)
	./$(TEST_NAME)

t:
	${CXX} -o tmp tmp.cpp
	./tmp

.PHONY: all clean fclean re test

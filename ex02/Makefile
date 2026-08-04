SRCS = main.cpp PmergeMe.cpp

NAME = PmergeMe

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJS = $(SRCS:%.cpp=%.o)

DEPS = PmergeMe.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $^ $(CXXFLAGS) -o $@

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
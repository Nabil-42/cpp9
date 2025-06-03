CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -g

NAME = PmergeMe
SRCS = main.cpp
OBJDIR = obj
OBJS = $(SRCS:.cpp=.o)
OBJS := $(addprefix $(OBJDIR)/, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

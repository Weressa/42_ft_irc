NAME = ircserv

FLAG = -Wall -Wextra -Werror -std=c++98 -Iinc

SRCS = main.cpp \

OBJDIR = ./obj

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
			mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
			c++ $(FLAG) -o $(NAME) $(OBJS)
	
$(OBJDIR)/%.o: %.cpp
			mkdir -p $(dir $@)
			c++ $(FLAG) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all
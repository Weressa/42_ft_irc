NAME 		= ircserv
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
SRCS_DIR	= src
OBJS_DIR	= obj
HDRS_DIR	= hdr
SRCS_FILES	= main.cpp \
			  Parser.cpp \
			  ServerConf.cpp \
			  PollEvent.cpp \
			  ServerRun.cpp \
			  ClientAddRemove.cpp \
			  ClientIO.cpp \
			  ClientGetters.cpp \
			  CommandHandler.cpp
SRCS		= $(patsubst %, $(SRCS_DIR)/%, $(SRCS_FILES))
OBJS		= $(patsubst $(SRCS_DIR)/%.cpp, $(OBJS_DIR)/%.o, $(SRCS))
DEPS		= $(patsubst %.o, %.d, $(OBJS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -I $(HDRS_DIR) $^ -o $(NAME)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -I $(HDRS_DIR) -c $< -o $@


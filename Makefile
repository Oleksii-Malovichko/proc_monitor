NAME = monitor

SRCS = main.c utils.c

CC = cc

GNL_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

all: $(NAME)

$(NAME): Makefile
	@echo "Compiling"
	@$(CC) $(SRCS) $(GNL_SRCS) -o $(NAME)
	@echo "Ready!"

clean:
	@echo "Removing $(NAME)"
	@rm -rf $(NAME)

fclean: clean

re: clean all
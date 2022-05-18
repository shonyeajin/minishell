CC=gcc
CFLAGS= #-Wall -Werror -Wextra

NAME=minishell
SOURCES= main.c
OBJECTS= $(SOURCES:.c=.o)

all : $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJECTS)
	$(MAKE) all -C libft/
	cp libft/libft.a libft.a
	$(CC) $(CFLAGS) $(OBJECTS) libft.a -o $(NAME) -lncurses

clean:
	rm -rf $(OBJECTS) libft.a

fclean: clean
	rm -rf $(NAME)

re : clean all

CC= gcc
CFLAGS = -Wall -Werror -Wextra

NAME= libft.a
SOURCES = ft_strdup.c get_next_line.c ft_bzero.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strcmp.c ft_memset.c ft_calloc.c ft_putstr_fd.c ft_putchar_fd.c ft_putstr_fd.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJECTS)
	ar -cr $@ $^

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re : clean all

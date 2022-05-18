#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include "./libft/libft.h"

#define HISTORY_FILE "./.minishell_history"
#define HISTORY_SIZE 20

typedef struct s_token
{
	char *s;
	int info;
}		t_token;

typedef struct s_pipe
{
	char *cmd;
	char *cmd_size;
	int p_read;
	int p_write;
	int next;
	pid_t child;
}		t_pipe;

typedef struct s_index
{
	int i;
	int j;
	int quote;
}		t_index;

typedef struct s_hist
{
	void *content;
	struct s_hist *next;
	struct s_hist *prev;
} t_hist;

typedef struct s_term
{
	char *up;
	char *down;
	char *cariage_return;
	char *clean_line;
	char *end;
	char *start;
}	t_term;


typedef struct s_data
{
	char *prompt;
	char *input;
	int status;
	int status_signal;
	char **envp;
	char *path;
	int fd_in;
	int fd_out;
	int redir;
	int in_terminal;
	struct termios origin;
	struct termios modified;
	t_hist *history_head;
	t_hist *history_index;
	t_term *term;
}	t_data;

#endif

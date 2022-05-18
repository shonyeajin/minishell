#include "minishell.h"

t_data g_data; //전역변수를 쓸 수 밖에 없는 이유: sighandler에 인자를 전달해야 하는데 sigaction이 허용함수가 아니라서 전역변수를 쓸수 밖에 없음.

int sizefunc_envp(char **envp)
{
	int i;

	i=0;
	while (envp[i])
		i++;
	return (++i);
}

char **copy_envp(char **envp)
{
	char **data_envp;
	int i;

	i=0;
	data_envp=(char **)malloc(sizeof(char *)*sizefunc_envp(envp));
	if (!data_envp)
		exit(EXIT_FAILURE);
	while (envp[i])
	{
		data_envp[i]=ft_strdup(envp[i]);
		i++;
	}
	data_envp[i]=0;
	return (data_envp);
}

void init_data_func(t_data *data, char **envp)
{
	data->prompt="\x1b[32m[\x1b[33mminishell\xb[32]>\x1b[0m ";
	data->status=0;
	data->status_signal=0;
	data->input=NULL;
	data->envp=copy_envp(envp);
	if (!data->envp)
		exit(EXIT_FAILURE);
	data->path=getcwd(NULL, 0);
	data->fd_in=0;
	data->fd_out=1;
	data->redir=1;
	data->history_head=NULL;
	data->history_index=NULL;
}

t_hist *add_node_func(void *s)
{
	t_hist *new;

	new=(t_hist *)malloc(sizeof(t_hist));
	ft_memset(new, 0, sizeof(t_hist));
	if (new)
		new->content=s;
	new->prev=NULL;
	return (new);
}

void add_history_func(t_hist **head, char *cmd)
{
	t_hist *new;

	new=NULL;
	if (*cmd)
	{
		if (((*head) && ft_strcmp((*head)->content, cmd)) || !(*head))
			new=add_node_func(ft_strdup(cmd));
		if (new)
		{
			if (!(*head))
				*head=new;
			else
			{
				new->next=*head;
				(*head)->prev=new;
				*head=new;
			}
		}
	}
}

void get_history_func(int fd, t_data *data)
{
	char *line;
	int ret;

	line=NULL;
	ret=get_next_line(fd, &line);
	while (ret>=0)
	{
		if (*line !='\0')
			add_history_func(&data->history_head, line);
		//if (line!=NULL)
		free(line);
		if(ret==0)
			break;
		ret=get_next_line(fd, &line);
	}
}

void init_history_func(t_data *data)
{
	int fd;

	fd=open(HISTORY_FILE, O_RDONLY);
	if (fd>=0)
	{
		get_history_func(fd, data);
		close(fd);
	}
}

void free_func_envp(char **envp)
{
	int i;
	int envp_len;

	i=0;
	envp_len=sizefunc_envp(envp);
	while (i< envp_len)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void free_func_data(t_data *data, int code)
{
	free_func_envp(data->envp);
	free(data->path);
	ft_putstr_fd("exit\n",2);
	exit(code);
}

void set_termcaps(t_data *data)
{
	data->term->start=tgetstr("ks", 0);
	data->term->end=tgetstr("ke",0);
	data->term->up=tgetstr("ku", 0);
	data->term->down=tgetstr("kd", 0);
	data->term->clean_line=tgetstr("dl", 0);
	data->term->cariage_return=tgetstr("cr", 0);
	if(!data->term->start || !data->term->end || !data->term->up || !data->term->down || !data->term->clean_line || !data->term->cariage_return)
		free_func_data(data, EXIT_FAILURE);

}

int set_history_func(t_data *data)
{
	char *type;
	int i;

	if (isatty(STDIN_FILENO))
	{
		type=getenv("TERM");
		if (!type)
		{
			write(STDOUT_FILENO, "TERM config not set, exiting...\n", 34);
			free_func_data(data, EXIT_FAILURE);
		}
		i=tgetent(0, type);//터미널 제어위해서. termcap.h
		data->term=ft_calloc(1, sizeof(t_term));
		if (i !=1 || !data->term)
			free_func_data(data, EXIT_FAILURE);
		ft_bzero(&data->modified, sizeof(struct termios));
		tcgetattr(0, &data->origin);
		tcgetattr(0, &data->modified);
		data->modified.c_iflag &= ~(IXON | ISTRIP | INPCK | PARMRK | INLCR | ICRNL | BRKINT | IGNBRK);//입력에 관한 플래그 비트 토글하기
		data->modified.c_lflag &= ~(ICANON | ECHO);//로컬에 대한 플래그 비트 토글하기, 캐노니칼, 애코 사용가능 한지
		set_termcaps(data);
	}
	return (1);
}

void handler_func(int signal)
{
	if (signal==SIGINT)
	{
		g_data.status=130;
		if (g_data.input)
		{
			ft_putchar_fd('\n',2);
			ft_putstr_fd(g_data.prompt,2);
		}
		if (g_data.input)
			free(g_data.input);
		g_data.input=ft_strdup("\0");
		g_data.history_index=NULL;
	}
}

void init_signal_func(void)
{
	if (signal(SIGQUIT, handler_func)==SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGINT, handler_func)==SIG_ERR)
		exit(EXIT_FAILURE);
}


int main(int argc, char *argv[], char *envp[])
{

	init_data_func(&g_data, envp);
	init_history_func(&g_data);
	set_history_func(&g_data);
	init_signal_func();


}

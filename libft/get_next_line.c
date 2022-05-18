#include "libft.h"

static int	backup_func(int fd, char **line, char **backup)
{
	if (fd < 0 || !line || !BUFFER_SIZE)
		return (-1);
	if (backup[fd])
	{
		*line = ft_strdup(backup[fd]);
		ft_bzero(backup[fd], ft_strlen(backup[fd]));
		free(backup[fd]);
		backup[fd] = NULL;
	}
	else
		*line = ft_strdup("");
	if (!*line)
		return (-1);
	return (0);
}

static int	free_and_exit(char *str)
{
	free (str);
	return (-1);
}

static int	out_func(int fd, char **line, char **backup, char *nl_p)
{
	if (**line == 0)
	{
		if (backup[fd])
			free(backup[fd]);
		return (0);
	}
	if (nl_p != NULL)
	{
		backup[fd] = ft_strdup(nl_p + 1);
		if (!backup[fd])
			return (free_and_exit(*line));
		ft_bzero(nl_p, ft_strlen(nl_p));
		if (*backup[fd] == 0)
		{
			free(backup[fd]);
			backup[fd] = NULL;
		}
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*backup[FD_SETSIZE] = {0};
	char		buffer[BUFFER_SIZE + 1];
	int			func_ret;
	char		*nl_p;

	func_ret = backup_func(fd, line, backup);
	if (func_ret == -1)
		return (-1);
	nl_p = ft_strchr(*line, '\n');
	while (nl_p == NULL)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		func_ret = read(fd, buffer, BUFFER_SIZE);
		if (func_ret < 0)
			return (free_and_exit(*line));
		if (func_ret == 0)
			break ;
		nl_p = *line;
		*line = ft_strjoin(*line, buffer);
		if (!*line)
			return (free_and_exit(nl_p));
		free(nl_p);
		nl_p = ft_strchr(*line, '\n');
	}
	return (out_func(fd, line, backup, nl_p));
}

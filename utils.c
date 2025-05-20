#include "monitor.h"

void	*mymalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(1);
	}
	return ptr;
}

int	isNum(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	return 1;
}

void	free_info(t_Info *info)
{
	if (info->cmd)
		free(info->cmd);
	if (info->pid)
		free(info->pid);
	if (info->status)
		free(info->status);
	if (info->user)
		free(info->user);
	free(info);
}

char	*beauty_name(char *name, char *find)
{
	int i = strlen(find);
	char *new_name;

	if (!name)
		return NULL;
	while (name[i] && isspace(name[i]))
		i++;
	new_name = strdup(name + i);
	free(name);
	new_name[strlen(new_name) - 1] = '\0';
	return new_name;
}

int get_terminal_height()
{
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
		return 24;
	return w.ws_row;
}

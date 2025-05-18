#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <ctype.h>
#include <sys/types.h>

#include "get_next_line/get_next_line.h"

typedef struct t_Info
{
	char *pid;
	char *user;
	char *cmd;
	char *status;
}	t_Info;

void	*mymalloc(size_t size);
int	isNum(char *str);
void	free_info(t_Info *info);
char	*beauty_name(char *name, char *find);

#endif
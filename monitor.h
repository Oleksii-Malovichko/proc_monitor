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
#include <sys/ioctl.h>

#include "get_next_line/get_next_line.h"

typedef struct t_Info
{
	char *pid;
	char *user;
	char *cmd;
	char *status;
	char *mem;
}	t_Info;

typedef struct InfoNode
{
	t_Info *info;
	struct InfoNode *next;
}	InfoNode;

void	*mymalloc(size_t size);
int	isNum(char *str);
void	free_info(t_Info *info);
char	*beauty_name(char *name, char *find);
int get_terminal_height();

#endif
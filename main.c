/*  Что показать:
PID	имя папки /proc/[pid]
Имя процесса	/proc/[pid]/comm или status
Статус	/proc/[pid]/status → State:
CPU (%)	из /proc/[pid]/stat + /proc/stat
Mem (KB)	/proc/[pid]/status → VmRSS:
Команда	/proc/[pid]/cmdline
Пользователь	UID → /proc/[pid]/status → Uid: → getpwuid

man proc - описаны все поля stat, statm, status и др.

Советы:
Используй man proc — там описаны все поля stat, statm, status и др.

Для CPU-расчётов нужно две выборки: текущее и предыдущее значение, чтобы вычислить дельту.

Порядок полей в /proc/[pid]/stat строгий, но числовой — не забывай про кавычки в имени команды:
пример: 1234 (bash) S ...*/

/* 
Сортировка по имени и по возрастанию pid */

#include "monitor.h"

void clear_screen()
{
    // ANSI escape sequence to clear screen and move cursor to top-left
    // printf("\033[H\033[J");
	printf("\033c");
	fflush(stdout);
}

void	show_header()
{
	printf("%-10s %-15s %-10s %-10s\n", "PID", "STATE", "USER", "COMMAND");
	printf("-------------------------------------------------\n");
}

void	print_structure(t_Info *info)
{
	printf("%-10s %-15s %-10s %-10s\n", info->pid, info->status, info->user, info->cmd);
}

char	*get_status(t_Info *info, char *find)
{
	int fd;
	char path[100];
	char *name;

	snprintf(path, sizeof(path), "/proc/%s/status", info->pid);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		printf("path: %s\n", path);
		return NULL;
	}
	name = get_next_line(fd);
	while (name)
	{
		if (strncmp(name, find, strlen(find)) == 0)
			break;
		free(name);
		name = get_next_line(fd);
	}
	close(fd);
	return (beauty_name(name, find));
}

char	*get_user(t_Info *info, char *find)
{
	char *uid_field = get_status(info, find);
	char *uid;
	int i = 0;
	int j = 0;
	struct passwd *pwd;

	if (!uid_field)
		return NULL;
	while (uid_field[i] && !isspace(uid_field[i]))
		i++;
	uid = mymalloc(i + 1);
	uid[i] = '\0';
	while (j < i)
	{
		uid[j] = uid_field[j];
		j++;
	}
	pwd = getpwuid(atoi(uid));
	free(uid_field);
	free(uid);
	return strdup(pwd->pw_name);
}

int	skip_entry(struct dirent *entry)
{
	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		return 1;
	if (!isNum(entry->d_name))
		return 1;
	return 0;
}

t_Info *create_info_from_entry(struct dirent *entry)
{
	t_Info *info = (t_Info *)mymalloc(sizeof(t_Info));
	if (!info)
		return NULL;

	memset(info, 0, sizeof(t_Info));
	info->pid = strdup(entry->d_name);
	if (!info->pid)
	{
		free_info(info);
		return NULL;
	}
	info->cmd = get_status(info, "Name:");
	if (!info->cmd)
	{
		free_info(info);
		return NULL;
	}
	info->status = get_status(info, "State:");
	if (!info->status)
	{
		free_info(info);
		return NULL;
	}
	info->user = get_user(info, "Uid:");
	if (!info->user)
	{
		free_info(info);
		return NULL;
	}
	return info;
}

InfoNode *add_to_list(InfoNode *head, t_Info *info)
{
	InfoNode *node = (InfoNode *)malloc(sizeof(InfoNode));
	if (!node)
		return head;
	node->info = info;
	node->next = NULL;
	if (!head)
		return node;
	InfoNode *tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return head;
}

void	free_lst(InfoNode *head)
{
	InfoNode *current = head;
	InfoNode *next;

	while (current)
	{
		next = current->next;
		if (current->info)
			free_info(current->info);
		free(current);
		current = next;
	}
}

int	start_monitoring(char *name)
{
	InfoNode *head = NULL;
	t_Info *info = {0};
	struct dirent *entry;
	int count = 0;
	DIR *dir;

	dir = opendir("/proc");
	if (!dir)
	{
		perror("opendir");
		return 1;
	}
	show_header();
	while ((entry = readdir(dir)) != NULL)
	{
		if (skip_entry(entry))
			continue;
		info = create_info_from_entry(entry);
		if (!info)
			continue;
		if (name && strcmp(info->user, name) != 0)
		{
			free_info(info);
			continue;
		}
		head = add_to_list(head, info);
		// print_structure(info);
		// free_info(info);
		// count++;
	}
	closedir(dir);
	InfoNode *current = head;
	while (current && count < get_terminal_height() - 3)
	{
		print_structure(current->info);
		InfoNode *next = current->next;
		current = next;
		count++;
	}
	free_lst(head);
    return 0;
}

int main(int argc, char *argv[])
{
	// if (argc != 2)
	// {
	// 	printf("USAGE: %s name_user\n", argv[0]);
	// 	return 1;
	// }
	int i = 0;

	while(1)
	{
		clear_screen();
		start_monitoring(NULL);
		// usleep(300000);
		sleep(2);
		i++;
	}
    return 0;
}

// printf("My fake top screen - %d\n", i);
// printf("CPU: %d%%\n", rand() % 100);
// printf("RAM: %dMB\n", rand() % 8192);

// void	get_info()
// {
// 	char proc[300] = "/proc/";
// 	struct dirent *entry;
// 	char *all_path = NULL;
// 	DIR *dir;
// 	const char *temp = "/proc/";

// 	dir = opendir(proc);
// 	if (!dir)
// 		return (perror("opendir"));
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		// clear_screen();
// 		strcat(proc, entry->d_name);
// 		strcat(proc, "/status");
// 		printf("Found: %s\n", proc);
// 		// if ()
// 		// fflush(stdout);
// 		bzero(proc, 300);
// 		strcpy(proc, temp);
// 		// sleep(1);
// 	}
// 	closedir(dir);
// }
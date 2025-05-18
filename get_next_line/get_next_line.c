/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:43:14 by omalovic          #+#    #+#             */
/*   Updated: 2024/11/15 14:25:11 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_copy_bytes(char *result, char *src1, char *src2, int i2)
{
	int	i1;
	int	k;

	i1 = ft_strlen(src1);
	k = 0;
	while (k < i1)
	{
		result[k] = src1[k];
		k++;
	}
	k = 0;
	while (k < i2)
	{
		result[i1] = src2[k];
		i1++;
		k++;
	}
	result[i1] = '\0';
	free(src1);
	return (result);
}

char	*gen_str(char *src1, char *src2, int i2)
{
	int		i1;
	char	*result;

	if (!src2)
		return (NULL);
	if (!src1)
		return (ft_copystr(&src2, i2, 1));
	i1 = ft_strlen(src1);
	if (i1 == -1 || i1 < 0 || i2 < 0)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (i1 + i2 + 1));
	if (!result)
		return (NULL);
	result = ft_copy_bytes(result, src1, src2, i2);
	if (!result)
		return (NULL);
	return (result);
}

char	*get_remainder(char *buffer, int checker_result, int bytes_read)
{
	char	*remainder;
	int		i;
	int		size;

	size = bytes_read - checker_result;
	if (size <= 0)
		return (NULL);
	remainder = (char *)malloc(sizeof(char) * (size + 1));
	if (!remainder)
		return (NULL);
	i = 0;
	while (i < size)
	{
		remainder[i] = buffer[checker_result + i];
		i++;
	}
	remainder[size] = '\0';
	return (remainder);
}

int	deal_with_remainder(char **remainder, char **result)
{
	char	*new_remainder;

	if (*remainder)
	{
		if (checker(*remainder) != -1)
		{
			*result = gen_str(NULL, *remainder, checker(*remainder));
			new_remainder = get_remainder(*remainder,
					checker(*remainder), ft_strlen(*remainder));
			free(*remainder);
			*remainder = new_remainder;
			if (*remainder)
				return (1);
			else if (*result)
				return (1);
			else
				return (-1);
		}
		*result = ft_copystr(remainder, ft_strlen(*remainder), 1);
		if (!*result)
			return (-1);
		free(*remainder);
		*remainder = NULL;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	char		*result;
	static char	*remainder = NULL;

	result = NULL;
	if (deal_with_remainder(&remainder, &result) == 1)
		return (result);
	if (deal_with_remainder(&remainder, &result) == -1)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(remainder), free(result), NULL);
		if (bytes_read == 0)
			return (handle_remainder(&result));
		buffer[bytes_read] = '\0';
		if (checker(buffer) != -1)
			return (process_buffer(result, buffer, bytes_read, &remainder));
		result = gen_str(result, buffer, bytes_read);
	}
	return (NULL);
}

/* int main()
{
	int fd = open("/Users/omalovic/get_next_line_project/file", O_RDONLY);
	if (fd == -1)
		return 1;
	// printf("firstcall:\n%s\nend of first call...\n", get_next_line(fd));
	// printf("secondcall:\n%s\nend of second call...\n", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
} */
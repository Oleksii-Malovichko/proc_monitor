/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:43:10 by omalovic          #+#    #+#             */
/*   Updated: 2024/11/15 14:23:11 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	checker(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			return (i + 1);
		}
		i++;
	}
	return (-1);
}

char	*ft_copystr(char **remainder, int checker_result, int sign)
{
	char	*result;
	int		i;

	if (!*remainder || checker_result <= 0)
		return (NULL);
	if (sign == 1)
	{
		result = (char *)malloc(sizeof(char) * (checker_result + 1));
		if (!result)
		{
			free(*remainder);
			*remainder = NULL;
			return (NULL);
		}
	}
	i = 0;
	while (i < checker_result)
	{
		result[i] = (*remainder)[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*handle_remainder(char **result)
{
	if (*result)
		return (*result);
	return (NULL);
}

char	*process_buffer(char *result, char *buffer,
		ssize_t bytes_read, char **remainder)
{
	int	check_result;

	check_result = checker(buffer);
	result = gen_str(result, buffer, check_result);
	*remainder = get_remainder(buffer, check_result, bytes_read);
	if (!*remainder)
		return (handle_remainder(&result));
	return (result);
}

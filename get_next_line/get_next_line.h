/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:43:36 by omalovic          #+#    #+#             */
/*   Updated: 2024/11/15 14:24:58 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*get_remainder(char *buffer, int checker_result, int bytes_read);
int		checker(char *buffer);
char	*ft_copystr(char **remainder, int checker_result, int sign);
char	*handle_remainder(char **result);
char	*process_buffer(char *result, char *buffer,
			ssize_t bytes_read, char **remainder);
char	*gen_str(char *src1, char *src2, int i2);

#endif

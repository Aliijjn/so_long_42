/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_read.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 11:47:10 by akuijer       #+#    #+#                 */
/*   Updated: 2024/02/01 12:16:38 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define BUFFER_SIZE 100

static char	*loop(int fd, char *buffer)
{
	int	read_result;

	read_result = read(fd, buffer, BUFFER_SIZE);
	if (read_result <= 0)
	{
		free(buffer);
		return (NULL);
	}
	while (1)
	{
		buffer = ft_realloc(buffer,
				(int)ft_strlen(buffer) + 1, BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		read_result = read(fd, buffer + ft_strlen(buffer), BUFFER_SIZE);
		if (read_result < 0)
			return (NULL);
		if (read_result < BUFFER_SIZE)
			return (buffer);
	}
}

char	*read_file(int fd)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer = loop(fd, buffer);
	while (buffer[i])
	{
		if (buffer[i] == '\n' && buffer[i + 1] == '\n')
		{
			free(buffer);
			return (NULL);
		}
		i++;
	}
	return (buffer);
}

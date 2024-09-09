/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc_tools.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 13:48:17 by akuijer       #+#    #+#                 */
/*   Updated: 2024/02/01 14:54:37 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*returns zero when only c is found in a string, 
otherwise returns a ptr to the first instance of s[i] != c*/
char	*ft_nstrchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != (char)c)
		{
			return (s + i);
		}
		i++;
	}
	return (0);
}

void	*ft_realloc(void *ptr_in, int size, int add)
{
	char	*ptr_out;
	int		i;

	i = 0;
	ptr_out = ft_calloc(size + add, 1);
	if (!ptr_out)
	{
		free(ptr_in);
		return (NULL);
	}
	while (i < size && i < size + add)
	{
		*((char *)ptr_out + i) = *((char *)ptr_in + i);
		i++;
	}
	free(ptr_in);
	return (ptr_out);
}

bool	can_enter(t_cache *lvl, int x, int y)
{
	if (lvl->map[y][x] == '1')
	{
		return (false);
	}
	return (true);
}

bool	v2_compare(t_vector2 a, t_vector2 b)
{
	if (a.x == b.x && a.y == b.y)
	{
		return (true);
	}
	return (false);
}

void	throw_error(char *s)
{
	write(2, s, ft_strlen(s));
	exit(1);
}

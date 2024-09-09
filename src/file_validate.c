/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_validate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 13:56:58 by akuijer       #+#    #+#                 */
/*   Updated: 2024/02/02 11:46:51 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_coin(t_cache *level, t_vector2 pos)
{
	if (!level->coins)
	{
		level->coins = ft_calloc(2, sizeof(t_vector2));
	}
	else
	{
		level->coins = ft_realloc(level->coins, (level->coins_count + 1)
				* sizeof(t_vector2), sizeof(t_vector2));
	}
	if (!level->coins)
	{
		throw_error("Realloc error");
	}
	level->coins[level->coins_count] = (t_vector2){pos.x, pos.y};
	level->coins_count++;
	level->coins_max++;
}

int	validate_coord(t_cache *level, int x, int y)
{
	if (!ft_strchr("01CEP", level->map[y][x]))
		return (UNKNOWN_SYMBOL);
	if (level->map[y][x] == 'E' && level->exit.x)
		return (EXIT_COUNT);
	if (level->map[y][x] == 'E' && !level->exit.x)
		level->exit = (t_vector2){x, y};
	if (level->map[y][x] == 'P' && level->player.x)
		return (PLAYER_COUNT);
	if (level->map[y][x] == 'P' && !level->player.x)
		level->player = (t_vector2){x, y};
	if (level->map[y][x] == 'C')
		add_coin(level, (t_vector2){x, y});
	return (0);
}

int	validate_line(t_cache *level, int y)
{
	int			str_len;
	static int	prev_str_len;

	str_len = ft_strlen(&level->map[y][0]);
	if (str_len < 3)
	{
		return (UNPLAYABLE_LEVEL);
	}
	if ((!y || !&level->map[y + 1][0]) && ft_nstrchr(&level->map[y][0], '1'))
	{
		return (INVALD_BORDER);
	}
	if (y && &level->map[y + 1][0] &&
			(level->map[y][0] != '1' || level->map[y][str_len - 1] != '1'))
	{
		return (INVALD_BORDER);
	}
	if (prev_str_len && str_len != prev_str_len)
	{
		return (INCON_WIDTH);
	}
	level->size.x = str_len;
	prev_str_len = str_len;
	return (0);
}

int	validate_file(t_cache *level, int x, int y)
{
	int	result;

	while (&level->map[y][0])
	{
		x = 0;
		while (level->map[y][x])
		{
			result = validate_coord(level, x++, y);
			if (result)
				return (result);
		}
		result = validate_line(level, y++);
		if (result)
			return (result);
	}
	level->size.y = y;
	if (!level->coins)
		return (NO_COLLECTABLE);
	if (!level->exit.x)
		return (EXIT_COUNT);
	if (!level->player.x)
		return (PLAYER_COUNT);
	if (!check_all_paths(*level))
		return (UNPLAYABLE_LEVEL);
	return (OK);
}

t_cache	handle_file(int fd)
{
	char	*map;
	t_cache	level;
	int		result;

	map = read_file(fd);
	close(fd);
	if (!map)
		throw_error("Error whilst reading file/ gap in map");
	level = (t_cache){{NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL}, NULL, (t_vector2){0, 0},
		(t_vector2){0, 0}, (t_vector2){0, 0},
		NULL, 0, 0, 0, ft_split(map, '\n')};
	free(map);
	if (!level.map)
		throw_error("Split Error");
	result = validate_file(&level, 0, 0);
	if (result)
	{
		if (level.coins)
			free(level.coins);
		ft_printf("Map error %i\n", result);
		throw_error("Invalid Map");
	}
	return (level);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_algorithm.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:53:59 by akuijer       #+#    #+#                 */
/*   Updated: 2024/02/02 11:47:06 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	not_visited(int level_width, t_vector2 pos, bool *table)
{
	if (table[pos.x + pos.y * level_width])
	{
		return (false);
	}
	table[pos.x + pos.y * level_width] = true;
	return (true);
}

bool	check_paths(t_cache level, t_vector2 pos, t_vector2 end, bool *table)
{
	if (v2_compare(pos, end))
		return (true);
	if (pos.x && level.map[pos.y][pos.x - 1] != '1' && \
		not_visited(level.size.x, (t_vector2){pos.x - 1, pos.y}, table) && \
		check_paths(level, (t_vector2){pos.x - 1, pos.y}, end, table))
		return (true);
	if (pos.x < level.size.x - 1 && level.map[pos.y][pos.x + 1] != '1' && \
		not_visited(level.size.x, (t_vector2){pos.x + 1, pos.y}, table) && \
		check_paths(level, (t_vector2){pos.x + 1, pos.y}, end, table))
		return (true);
	if (pos.y && level.map[pos.y - 1][pos.x] != '1' && \
		not_visited(level.size.x, (t_vector2){pos.x, pos.y - 1}, table) && \
		check_paths(level, (t_vector2){pos.x, pos.y - 1}, end, table))
		return (true);
	if (pos.y < level.size.y - 1 && level.map[pos.y + 1][pos.x] != '1' && \
		not_visited(level.size.x, (t_vector2){pos.x, pos.y + 1}, table) && \
		check_paths(level, (t_vector2){pos.x, pos.y + 1}, end, table))
		return (true);
	return (false);
}

bool	check_all_paths(t_cache level)
{
	int		i;
	bool	*table;

	i = 1;
	table = ft_calloc(level.size.x * level.size.y, sizeof(bool));
	if (!table)
		throw_error("Malloc Error");
	if (!check_paths(level, level.player, level.coins[0], table))
		return (free(table), false);
	ft_bzero(table, level.size.x * level.size.y * sizeof(bool));
	while (i < level.coins_count)
	{
		if (!check_paths(level, level.coins[i - 1], level.coins[i], table))
			return (free(table), false);
		ft_bzero(table, level.size.x * level.size.y * sizeof(bool));
		i++;
	}
	if (!check_paths(level, level.coins[i - 1], level.exit, table))
		return (free(table), false);
	free(table);
	return (true);
}

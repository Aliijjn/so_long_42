/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_tools.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 13:09:06 by akuijer       #+#    #+#                 */
/*   Updated: 2024/02/01 17:49:45 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_logic(t_cache *lvl, t_vector2 vel)
{
	int	i;

	i = 0;
	draw_texture(lvl, lvl->player.x, lvl->player.y, false);
	lvl->player.x += vel.x;
	lvl->player.y += vel.y;
	draw_texture(lvl, 0, 0, true);
	printf("Steps taken: %i\n", ++lvl->steps_taken);
	while (lvl->coins_count && i < lvl->coins_max)
	{
		if (v2_compare(lvl->player, lvl->coins[i]))
		{
			lvl->coins[i] = (t_vector2){0, 0};
			if (!--lvl->coins_count)
			{
				free(lvl->coins);
				lvl->coins = NULL;
			}
			lvl->map[lvl->player.y][lvl->player.x] = '0';
			break ;
		}
		i++;
	}
	if (lvl->map[lvl->player.y][lvl->player.x] == 'E' && lvl->coins_count == 0)
		end_game(true, true, NULL, lvl);
}

void	get_user_input(void *info)
{
	t_cache			*lvl;
	mlx_t			*mlx;
	static float	time;
	float			current_time;

	lvl = (t_cache *)info;
	mlx = ((t_cache *)info)->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		end_game(false, true, NULL, lvl);
	current_time = mlx_get_time();
	if (time + 0.09 > current_time)
		return ;
	time = current_time;
	if (mlx_is_key_down(mlx, MLX_KEY_A)
		&& can_enter(lvl, lvl->player.x - 1, lvl->player.y))
		game_logic(lvl, (t_vector2){-1, 0});
	if (mlx_is_key_down(mlx, MLX_KEY_D)
		&& can_enter(lvl, lvl->player.x + 1, lvl->player.y))
		game_logic(lvl, (t_vector2){1, 0});
	if (mlx_is_key_down(mlx, MLX_KEY_W)
		&& can_enter(lvl, lvl->player.x, lvl->player.y - 1))
		game_logic(lvl, (t_vector2){0, -1});
	if (mlx_is_key_down(mlx, MLX_KEY_S)
		&& can_enter(lvl, lvl->player.x, lvl->player.y + 1))
		game_logic(lvl, (t_vector2){0, 1});
}

void	init(t_cache *lvl)
{
	int	x;
	int	y;

	y = 0;
	while (lvl->map[y])
	{
		x = 0;
		while (lvl->map[y][x])
		{
			draw_texture(lvl, x, y, false);
			x++;
		}
		y++;
	}
	draw_texture(lvl, 0, 0, true);
}

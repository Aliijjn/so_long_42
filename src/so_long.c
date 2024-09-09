/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 11:06:57 by akuijer       #+#    #+#                 */
/*   Updated: 2024/02/05 14:01:19 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_texture(t_cache *lvl, int x, int y, bool draw_player)
{
	if (draw_player)
	{
		mlx_image_to_window(lvl->mlx, lvl->images[3],
			lvl->player.x * SIZE_B, lvl->player.y * SIZE_B);
		return ;
	}
	if (lvl->map[y][x] == '1')
	{
		mlx_image_to_window(lvl->mlx, lvl->images[0], x * SIZE_B, y * SIZE_B);
	}
	else if (lvl->map[y][x] == '0' || lvl->map[y][x] == 'P')
	{
		mlx_image_to_window(lvl->mlx, lvl->images[1], x * SIZE_B, y * SIZE_B);
	}
	else if (lvl->map[y][x] == 'C')
	{
		mlx_image_to_window(lvl->mlx, lvl->images[2], x * SIZE_B, y * SIZE_B);
	}
	else if (lvl->map[y][x] == 'E')
	{
		mlx_image_to_window(lvl->mlx, lvl->images[4], x * SIZE_B, y * SIZE_B);
	}
}

void	end_game(bool has_won, bool has_init, char *error_msg, t_cache *lvl)
{
	int	i;

	i = 0;
	if (has_won)
		write(1, "\nCongratulations, you've won! :)\n", 34);
	if (lvl->coins)
		free(lvl->coins);
	while (lvl->map[i])
		free(lvl->map[i++]);
	free(lvl->map);
	i = 0;
	while (i < 5)
	{
		if (lvl->textures[i])
			mlx_delete_texture(lvl->textures[i]);
		i++;
	}
	if (has_init)
		mlx_close_hook(lvl->mlx, &get_user_input, &lvl);
	mlx_close_window(lvl->mlx);
	mlx_terminate(lvl->mlx);
	if (error_msg)
		write(2, error_msg, ft_strlen(error_msg));
	exit(!(error_msg == NULL));
}

void	init_image(t_cache *lvl)
{
	int	i;

	i = 0;
	lvl->textures[0] = mlx_load_png("./sprites/bricks.png");
	lvl->textures[1] = mlx_load_png("./sprites/blank.png");
	lvl->textures[2] = mlx_load_png("./sprites/coin.png");
	lvl->textures[3] = mlx_load_png("./sprites/player.png");
	lvl->textures[4] = mlx_load_png("./sprites/exit.png");
	if (!(lvl->textures[0] && lvl->textures[1] && lvl->textures[2] && \
			lvl->textures[3] && lvl->textures[4]))
		end_game(false, false, "Error loading textures", lvl);
	while (i < 5)
	{
		lvl->images[i] = mlx_texture_to_image(lvl->mlx, lvl->textures[i]);
		if (!lvl->images[i])
			end_game(false, false, "Error loading images", lvl);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_cache	lvl;

	if (argc != 2)
		throw_error("Invalid arg count, should be 2");
	if (ft_strlen(argv[1]) >= 4 && \
			ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 5))
		throw_error("Map should be a .ber file");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		throw_error("Invalid FD");
	lvl = handle_file(fd);
	lvl.mlx = mlx_init(lvl.size.x * SIZE_B, \
			lvl.size.y * SIZE_B, "so_long", true);
	if (!lvl.mlx)
		end_game(false, false, "Initialise Error", &lvl);
	init_image(&lvl);
	init(&lvl);
	if (!mlx_loop_hook(lvl.mlx, get_user_input, &lvl))
		end_game(false, false, "Hook Error", &lvl);
	mlx_loop(lvl.mlx);
	end_game(false, true, "Exiting Programme", &lvl);
	return (0);
}

	// mlx_t *mlx = mlx_init(100, 100, "so_long", true);
	// if (!mlx)
	// {
	// 	return (1); // 323,303 bytes in 3,362 blocks
	// }
	// mlx_terminate(mlx);
	// return (0);
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 11:38:11 by akuijer       #+#    #+#                 */
/*   Updated: 2024/02/02 12:12:53 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include "../ft_printf/ft_printf.h"
# include "../MLX42/include/glad/glad.h"
# include "../MLX42/include/KHR/khrplatform.h"
# include "../MLX42/include/lodepng/lodepng.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
# ifndef SIZE_B
#  define SIZE_B 64
# endif

# ifndef E_STATUS
#  define E_STATUS
#  define OK 0
#  define INCON_WIDTH 1
#  define UNKNOWN_SYMBOL 2
#  define PLAYER_COUNT 3
#  define EXIT_COUNT 4
#  define NO_COLLECTABLE 5
#  define INVALD_BORDER 6
#  define UNPLAYABLE_LEVEL 7
# endif

typedef struct vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct cache
{
	mlx_texture_t	*textures[5];
	mlx_image_t		*images[5];
	mlx_t			*mlx;
	t_vector2		size;
	t_vector2		player;
	t_vector2		exit;
	t_vector2		*coins;
	int				steps_taken;
	int				coins_count;
	int				coins_max;
	char			**map;
}	t_cache;

char	*read_file(int fd);
void	*ft_realloc(void *ptr_in, int size, int add);
t_cache	handle_file(int fd);
char	*ft_nstrchr(char *s, int c);
void	*ft_realloc(void *ptr_in, int size, int add);
bool	check_all_paths(t_cache level);
bool	can_enter(t_cache *lvl, int x, int y);
bool	v2_compare(t_vector2 a, t_vector2 b);
void	throw_error(char *s);
void	end_game(bool has_won, bool has_init, char *error_msg, t_cache *lvl);
void	get_user_input(void *info);
void	game_logic(t_cache *lvl, t_vector2 vel);
void	init(t_cache *lvl);
void	draw_texture(t_cache *lvl, int x, int y, bool draw_player);

#endif
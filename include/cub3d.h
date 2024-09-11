/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:47 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/11 13:10:49 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1600
# define HEIGHT 1200
# define FAIL 1
# define SUCCESS 0
# define SPEED 5

typedef struct s_player
{
	float	player_x;
	float	player_y;
	float	player_dx;
	float	player_dy;
	float	player_a;
}	t_player;

typedef struct s_map
{
	char	**map;
}	t_map;

typedef struct s_minimap
{
	int		x;
	int		y;
	int		sx;
	int		sy;
	int		color;
	int		map_height;
	int		map_width;
	int		minimap_width;
	int		minimap_height;
	float	scale_x;
	float	scale_y;
}	t_minimap;

typedef struct s_cub3d_mlx
{
	void			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	t_player		player;
	t_map			map;
	t_minimap		minimap_var;
}	t_cub3d_mlx;

t_cub3d_mlx	*get_game(void);

//hooks
void		create_key_hooks(void);

//key funcions
void		esc_func(mlx_key_data_t key_data, void *param);
void		close_func(void *param);
void		player_movement(void);

//display
void		drawplayer_minimap(void);

//helper
void		ft_put_pixel(mlx_image_t *image, uint32_t x,
				uint32_t y, uint32_t color);

//minimap_utils
void		draw_on_minimap(t_minimap *minimap, char **map);

#endif
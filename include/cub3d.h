/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:47 by lglauch           #+#    #+#             */
/*   Updated: 2024/08/30 14:06:05 by lglauch          ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 600
# define FAIL 1
# define SUCCESS 0


typedef struct s_player
{
	float	player_x;
	float	player_y;
}	t_player;


typedef struct s_cub3d_mlx
{
	void		*mlx;
	void		*img;
	t_player	player;
}	t_cub3d_mlx;


t_cub3d_mlx	*get_game(void);

//hooks
void		create_key_hooks(void);

//key funcions
void		esc_func(mlx_key_data_t key_data, void *param);
void		close_func(void *param);

//display
void		drawplayer(void);


#endif
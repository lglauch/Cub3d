/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:40:34 by lglauch           #+#    #+#             */
/*   Updated: 2024/09/11 15:16:10 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_boundaries(float *x, float *y)
{
	if (*y < 0)
		*y = 0;
	if (*x < 0)
		*x = 0;
	if (*y > get_game()->minimap->height)
		*y = get_game()->minimap->height;
	if (*x > get_game()->minimap->width)
		*x = get_game()->minimap->width;
}

void	player_wasd(float angle_rad, float move_speed, float *x, float *y)
{
	void	*param;

	param = get_game()->mlx;
	if (mlx_is_key_down(param, MLX_KEY_W))
	{
		*x += -cos(angle_rad) * move_speed;
		*y += -sin(angle_rad) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_S))
	{
		*x += cos(angle_rad) * move_speed;
		*y += sin(angle_rad) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_A))
	{
		*x += -sin(angle_rad) * move_speed;
		*y += cos(angle_rad) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_D))
	{
		*x += sin(angle_rad) * move_speed;
		*y += -cos(angle_rad) * move_speed;
	}
	check_boundaries(x, y);
}

void	player_movement(void)
{
	void		*param;
	float		angle_rad;
	const float	move_speed = 1;
	const float	turn_speed = 5;

	param = get_game()->mlx;
	angle_rad = get_game()->player.player_a * (M_PI / 180);
	player_wasd(angle_rad, move_speed, &get_game()->player.player_x,
		&get_game()->player.player_y);
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
	{
		get_game()->player.player_a -= turn_speed;
		if (get_game()->player.player_a < 0)
			get_game()->player.player_a += 360;
	}
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
	{
		get_game()->player.player_a += turn_speed;
		if (get_game()->player.player_a >= 360)
			get_game()->player.player_a -= 360;
	}
}

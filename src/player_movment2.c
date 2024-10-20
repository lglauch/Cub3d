/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:09:00 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/20 16:55:29 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player_a_d(double move_speed, double new_x, double new_y)
{
	if (mlx_is_key_down(get_game()->mlx, MLX_KEY_A))
	{
		new_x -= cos(get_game()->player.player_a * M_PI / 180.0 + M_PI_2)
			* move_speed;
		new_y -= sin(get_game()->player.player_a * M_PI / 180.0 + M_PI_2)
			* move_speed;
	}
	if (mlx_is_key_down(get_game()->mlx, MLX_KEY_D))
	{
		new_x += cos(get_game()->player.player_a * M_PI / 180.0 + M_PI_2)
			* move_speed;
		new_y += sin(get_game()->player.player_a * M_PI / 180.0 + M_PI_2)
			* move_speed;
	}
}

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

void	ft_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (!image)
		return ;
	if (x > 0 && y > 0 && x < image->width && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

void	p_pos(float angle_rad, float move_speed, double *new_x, double *new_y)
{
	void	*param;

	param = get_game()->mlx;
	if (mlx_is_key_down(param, MLX_KEY_W))
	{
		*new_x += cos(angle_rad) * move_speed;
		*new_y += sin(angle_rad) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_S))
	{
		*new_x -= cos(angle_rad) * move_speed;
		*new_y -= sin(angle_rad) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_A))
	{
		*new_x -= cos(angle_rad + M_PI_2) * move_speed;
		*new_y -= sin(angle_rad + M_PI_2) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_D))
	{
		*new_x += cos(angle_rad + M_PI_2) * move_speed;
		*new_y += sin(angle_rad + M_PI_2) * move_speed;
	}
}

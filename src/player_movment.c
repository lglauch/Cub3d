/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:40:34 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/18 16:45:00 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_wasd(float angle_rad, float move_speed, float *x, float *y)
{
	void	*param;

	param = get_game()->mlx;
	if (mlx_is_key_down(param, MLX_KEY_W))
	{
		*x += cos(angle_rad) * move_speed;
		*y += sin(angle_rad) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_S))
	{
		*x -= cos(angle_rad) * move_speed;
		*y -= sin(angle_rad) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_A))
	{
		*x -= cos(angle_rad + M_PI_2) * move_speed;
		*y -= sin(angle_rad + M_PI_2) * move_speed;
	}
	if (mlx_is_key_down(param, MLX_KEY_D))
	{
		*x += cos(angle_rad + M_PI_2) * move_speed;
		*y += sin(angle_rad + M_PI_2) * move_speed;
	}
	check_boundaries(x, y);
}

void	update_player_direction(float player_a)
{
	float	angle_rad;

	angle_rad = player_a * (M_PI / 180);
	ray()->dirx = cos(angle_rad);
	ray()->diry = sin(angle_rad);
	ray()->planex = -0.66 * sin(angle_rad);
	ray()->planey = 0.66 * cos(angle_rad);
}

int	is_wall(double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= get_game()->map.map_width || map_y < 0
		|| map_y >= get_game()->map.map_height)
	{
		return (1);
	}
	return (get_game()->map.map[map_y][map_x] == '1');
}

void	move_player(double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = get_game()->player.player_x;
	new_y = get_game()->player.player_y;
	if (mlx_is_key_down(get_game()->mlx, MLX_KEY_W))
	{
		new_x += cos(get_game()->player.player_a * M_PI / 180.0) * move_speed;
		new_y += sin(get_game()->player.player_a * M_PI / 180.0) * move_speed;
	}
	if (mlx_is_key_down(get_game()->mlx, MLX_KEY_S))
	{
		new_x -= cos(get_game()->player.player_a * M_PI / 180.0) * move_speed;
		new_y -= sin(get_game()->player.player_a * M_PI / 180.0) * move_speed;
	}
	move_player_a_d(move_speed, new_x, new_y);
	if (!is_wall(new_x, get_game()->player.player_y))
		get_game()->player.player_x = new_x;
	if (!is_wall(get_game()->player.player_x, new_y))
		get_game()->player.player_y = new_y;
	update_player_direction(get_game()->player.player_a);
}

void	player_movement(void)
{
	float		angle_rad;
	const float	move_speed = 0.1;
	const float	turn_speed = 5;

	move_player(move_speed);
	angle_rad = get_game()->player.player_a * (M_PI / 180);
	player_wasd(angle_rad, move_speed, &get_game()->player.player_x,
		&get_game()->player.player_y);
	if (mlx_is_key_down(get_game()->mlx, MLX_KEY_LEFT))
	{
		get_game()->player.player_a -= turn_speed;
		if (get_game()->player.player_a < 0)
			get_game()->player.player_a += 360;
	}
	if (mlx_is_key_down(get_game()->mlx, MLX_KEY_RIGHT))
	{
		get_game()->player.player_a += turn_speed;
		if (get_game()->player.player_a >= 360)
			get_game()->player.player_a -= 360;
	}
}

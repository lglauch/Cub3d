/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:40:34 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/17 00:33:29 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_line(float dx, float dy, float player_x, float player_y)
{
	int		steps;
	float	stepx;
	float	stepy;
	int		i;

	steps = fmax((int)fabs(dx), fabs(dy));
	if (steps == 0)
		return ;
	stepx = dx / steps;
	stepy = dy / steps;
	i = 0;
	while (i <= steps)
	{
		ft_put_pixel(get_game()->minimap, player_x, player_y, 0xFFFFFF);
		player_x += stepx;
		player_y += stepy;
		i++;
	}
}

void	draw_line_direction(float angle_rad, float player_x, float player_y)
{
	float	line_length;
	float	dx;
	float	dy;

	line_length = 20;
	dx = player_x + cos(angle_rad) * line_length - player_x;
	dy = player_y + sin(angle_rad) * line_length - player_y;
	put_line(dx, dy, player_x, player_y);
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

void player_wasd(float angle_rad, float move_speed, float *x, float *y)
{
    void *param;

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

void update_player_direction(float player_a)
{
    float angle_rad;
	
	angle_rad = player_a * (M_PI / 180);
    ray()->dirx = cos(angle_rad);
    ray()->diry = sin(angle_rad);
    ray()->planex = -0.66 * sin(angle_rad);
    ray()->planey = 0.66 * cos(angle_rad);
}

int is_wall(double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;
	if (map_x < 0 || map_x >= get_game()->map.map_width || map_y < 0 || map_y >= get_game()->map.map_height)
    {
        return 1; // Treat out-of-bounds as a wall
    }
    return (get_game()->map.map[map_y][map_x] == '1');
}

// Function to move the player and update direction and plane vectors
void move_player(void)
{
    double move_speed = 0.1; // Adjust the speed as needed
    double new_x = get_game()->player.player_x;
    double new_y = get_game()->player.player_y;

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
	if (mlx_is_key_down(get_game()->mlx, MLX_KEY_A))
    {
        new_x -= cos(get_game()->player.player_a * M_PI / 180.0 + M_PI_2) * move_speed;
        new_y -= sin(get_game()->player.player_a * M_PI / 180.0 + M_PI_2) * move_speed;
    }
    if (mlx_is_key_down(get_game()->mlx, MLX_KEY_D))
    {
        new_x += cos(get_game()->player.player_a * M_PI / 180.0 + M_PI_2) * move_speed;
        new_y += sin(get_game()->player.player_a * M_PI / 180.0 + M_PI_2) * move_speed;
    }

    // Check for collisions
    if (!is_wall(new_x, get_game()->player.player_y))
        get_game()->player.player_x = new_x;
    if (!is_wall(get_game()->player.player_x, new_y))
        get_game()->player.player_y = new_y;
    update_player_direction(get_game()->player.player_a);
}

void	player_movement(void)
{
	void		*param;
	float		angle_rad;
	const float	move_speed = 0.1;
	const float	turn_speed = 5;

	param = get_game()->mlx;
	move_player();
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
	draw_line_direction(angle_rad,
		get_game()->player.player_x, get_game()->player.player_y);
}

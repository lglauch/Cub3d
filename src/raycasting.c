/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:06:45 by lglauch           #+#    #+#             */
/*   Updated: 2024/10/10 17:55:29 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void draw_line(float x0, float y0, float x1, float y1) {
//     int steps;
//     float stepX, stepY;
//     float x, y;
//     int i;

//     // Calculate the difference in both directions
//     float dx = x1 - x0;
//     float dy = y1 - y0;

//     // Determine the number of steps to take
//     steps = fmax(fabs(dx), fabs(dy));
//     stepX = dx / (float)steps;
//     stepY = dy / (float)steps;

//     x = x0;
//     y = y0;
//     for (i = 0; i <= steps; i++) {
//         ft_put_pixel(get_game()->minimap, round(x), round(y), 0xFFFFFF);

//         x += stepX;
//         y += stepY;
//     }
// }

//https://hackmd.io/@nszl/H1LXByIE2#player-direction-vector-and-camera-vector
//https://github.com/mcombeau/cub3D/blob/main/sources/render/raycasting.c#L95

void	init_values(void)
{
	ray()->posx = get_game()->player.player_x;
	ray()->posy = get_game()->player.player_y;
	ray()->dirx = -1; //initial direction vector, mabye needs change to get north west south east
	ray()->diry = 0; //same
	ray()->planex = 0;
	ray()->planey = 0.66;
}

void	cast_ray(int x)
{
	init_values();
	ray()->camerax = 2 * x / (double)WIDTH - 1;
	ray()->raydirx = ray()->dirx + ray()->planex * ray()->camerax;
	ray()->raydiry = ray()->diry + ray()->planey * ray()->camerax;
	ray()->deltadistx = fabs(1 / ray()->raydirx);
	ray()->deltadisty = fabs(1 / ray()->raydiry);
	// if (ray()->deltadistx == 0)
	// 	ray()->deltadistx = 1e30;
	// if (ray()->deltadisty == 0)
	// 	ray()->deltadisty = 1e30;
	ray()->mapx = (int)ray()->posx;
	ray()->mapy = (int)ray()->posy;
}

void	do_dda_calc(void)
{
	if (ray()->raydirx < 0)
	{
		ray()->stepx = -1;
		ray()->sidedistx = (ray()->posx - ray()->mapx) * ray()->deltadistx;
	}
	else
	{
		ray()->stepx = 1;
		ray()->sidedistx = (ray()->mapx + 1.0 - ray()->posx) * ray()->deltadistx;
	}
	if (ray()->raydiry < 0)
	{
		ray()->stepy = -1;
		ray()->sidedisty = (ray()->posy - ray()->mapy) * ray()->deltadisty;
	}
	else
	{
		ray()->stepy = 1;
		ray()->sidedisty = (ray()->mapy + 1.0 - ray()->posy) * ray()->deltadisty;
	}
}

void	dda_algo(void)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray()->sidedistx < ray()->sidedisty)
		{
			ray()->sidedistx += ray()->deltadistx;
			ray()->mapx += ray()->stepx;
			ray()->side = 0;
		}
		else
		{
			ray()->sidedisty += ray()->deltadisty;
			ray()->mapy += ray()->stepy;
			ray()->side = 1;
		}
		if (ray()->mapy < 0.25 || ray()->mapx < 0.25
			|| ray()->mapy > get_game()->map.map_height - 0.25
			|| ray()->mapx > get_game()->map.map_width - 1.25)
			break ;
		else if (get_game()->map.map[ray()->mapy][ray()->mapx] > '0')
			hit = 1;
	}
	// if (ray()->side == 0)
	// 	ray()->perpwalldist = (ray()->sidedistx - ray()->deltadistx);
	// else
	// 	ray()->perpwalldist = (ray()->sidedisty - ray()->deltadisty);
}

void	calculate_line_height()
{
	if (ray()->side == 0)
		ray()->wall_dist = (ray()->sidedistx - ray()->deltadistx);
	else
		ray()->wall_dist = (ray()->sidedisty - ray()->deltadisty);
	ray()->line_height = ((int)HEIGHT / ray()->wall_dist);
	ray()->draw_start = -(ray()->line_height) / 2 + HEIGHT / 2;
	if (ray()->draw_start < 0)
		ray()->draw_start = 0;
	ray()->draw_end = ray()->line_height / 2 + HEIGHT / 2;
	if (ray()->draw_end >= HEIGHT)
		ray()->draw_end = HEIGHT - 1;
	if (ray()->side == 0)
		ray()->wall_x = get_game()->player.player_y + ray()->wall_dist * ray()->diry;
	else
		ray()->wall_x = get_game()->player.player_x + ray()->wall_dist * ray()->dirx;
	ray()->wall_x -= floor(ray()->wall_x);
}

void	raycasting(void)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(x);
		do_dda_calc();
		dda_algo();
		calculate_line_height();
		// update_texture(x);
		x++;
	}
}